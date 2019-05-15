#pragma once
#ifndef FUCK_THIS_SO_MUCH
#define FUCK_THIS_SO_MUCH
#include<SDL2/SDL.h>
#include<SDL2/SDL2_gfxPrimitives.h>
#include "../../essential/Configuration.h"
//#include "../../primatives/Point.h"
#include "../../PointDelta.h"
//#include "../../essential/util.h"
#include "ControllerCommand.h" // TODO: Create folder/sub-folder for "controller" related
//#include<map>


/* Class to handle event handling(haha) less messily
 * with easier functionality to implement new events */ 
class Controller {
	private:
		std::map<int, ControllerCommand<PointDelta, Point>*> keydown;
		std::map<int, ControllerCommand<PointDelta, void(*)(PointDelta*)>*> keyup;
		Configuration config;
		PointDelta* target;
		//static const auto constexpr ADD = [](PointDelta* p, Point g) {(*p) += g;};
		//static const auto constexpr SUBTRACT = [](PointDelta* p, Point g) {(*p) -= g;};
		//static const auto constexpr X_ZERO = [](PointDelta* p) {p->xZero();};
		//static const auto constexpr Y_ZERO = [](PointDelta* p) {p->yZero();};
		//static const auto constexpr GREATER_ZERO = [](PointDelta* p,  void(*g)(PointDelta*)) {if (*p > 0) g(p);};
		//static const auto constexpr LESSER_ZERO = [](PointDelta* p,  void(*g)(PointDelta*)) {if (*p < 0) g(p);};
	public:
		Controller(Configuration config, PointDelta* target);
		~Controller();
		void handleEvents(SDL_Event e);
		
		static void ADD(PointDelta* p, Point g) {(*p) += g;}
		static void SUBTRACT(PointDelta* p, Point g) {(*p) -= g;}
		static void X_ZERO(PointDelta* p) {p->xZero();}
		static void Y_ZERO(PointDelta* p) {p->yZero();}
		static void GREATER_ZERO(PointDelta* p, void(*g)(PointDelta*)) {if(*p > 0) g(p);}
		static void LESSER_ZERO(PointDelta* p, void(*g)(PointDelta*)) {if(*p < 0) g(p);}
};
#endif
