#pragma once
#include<SDL2/SDL.h>
#include "essential/Configuration.h"
#include "primatives/Point.h"
#include "PointDelta.h"
#include "ControllerCommand.h" // TODO: Create folder/sub-folder for "controller" related
#include "essential/util.h"
#include<vector>
#include<map>

/* Class to handle event handling(haha) less messily
 * with easier functionality to implement new events */ 
class Controller {
	private:
		std::map<int, ControllerCommand<PointDelta, Point>*> keydown;
		std::map<int, ControllerCommand<PointDelta, void(*)(PointDelta*)>*> keyup;
		Configuration config;
		PointDelta* target;
		
		static const auto constexpr ADD = [](PointDelta* p, Point g) {(*p) += g;};
		static const auto constexpr SUBTRACT = [](PointDelta* p, Point g) {(*p) -= g;};
		static const auto constexpr X_ZERO = [](PointDelta* p) {p->xZero();};
		static const auto constexpr Y_ZERO = [](PointDelta* p) {p->yZero();};
		static const auto constexpr GREATER_ZERO = [](PointDelta* p,  void(*g)(PointDelta*)) {if (*p > 0) g(p);};
		static const auto constexpr LESSER_ZERO = [](PointDelta* p,  void(*g)(PointDelta*)) {if (*p < 0) g(p);};
		
		/** Please let this be temporary **/
		static const auto constexpr X_GREATER_ZERO = [](PointDelta* p,  void(*g)(PointDelta*)) {if (p->x() > 0) g(p);};
		static const auto constexpr X_LESSER_ZERO = [](PointDelta* p,  void(*g)(PointDelta*)) {if (p->x() < 0) g(p);};
		static const auto constexpr Y_GREATER_ZERO = [](PointDelta* p,  void(*g)(PointDelta*)) {if (p->y() > 0) g(p);};
		static const auto constexpr Y_LESSER_ZERO = [](PointDelta* p,  void(*g)(PointDelta*)) {if (p->y() < 0) g(p);};
	public:
		Controller(Configuration config, PointDelta* target) {
			this->config = config;
			this->target = target;		
			
			this->keydown[config["Right"]] = new ControllerCommand<PointDelta, Point>(Controller::ADD, this->target, this->target->getXPoint());
			this->keydown[config["Left"]] = new ControllerCommand<PointDelta, Point>(Controller::SUBTRACT, this->target, this->target->getXPoint());
			this->keydown[config["Up"]] = new ControllerCommand<PointDelta, Point>(Controller::SUBTRACT, this->target, this->target->getYPoint());
			this->keydown[config["Down"]] = new ControllerCommand<PointDelta, Point>(Controller::ADD, this->target, this->target->getYPoint());
			
			this->keyup[config["Right"]] = new ControllerCommand<PointDelta, void(*)(PointDelta*)>(Controller::GREATER_ZERO, this->target, Controller::X_ZERO);
			this->keyup[config["Left"]] = new ControllerCommand<PointDelta, void(*)(PointDelta*)>(Controller::LESSER_ZERO, this->target, Controller::X_ZERO);
			this->keyup[config["Up"]] = new ControllerCommand<PointDelta, void(*)(PointDelta*)>(Controller::LESSER_ZERO, this->target, Controller::Y_ZERO);
			this->keyup[config["Down"]] = new ControllerCommand<PointDelta, void(*)(PointDelta*)>(Controller::GREATER_ZERO, this->target, Controller::Y_ZERO);
		}
		
		~Controller() {}
		
		void handleEvents(SDL_Event e) {
			switch(e.type) {
				case SDL_KEYDOWN:
					if (e.key.repeat == 0)
						this->keydown[keyCodeFromEvent(e)]->execute();	
					break;
				case SDL_KEYUP:
					if (e.key.repeat == 0)
						this->keyup[keyCodeFromEvent(e)]->execute();
					break;
			}
		}
};
