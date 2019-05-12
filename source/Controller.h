#pragma once
#include<SDL2/SDL.h>
#include "essential/Configuration.h"
#include "primatives/Point.h"
#include "PointDelta.h"
#include "ControllerCommand.h" // TODO: Create folder/sub-folder for "controller" related
#include<vector>

/* Class to handle event handling(haha) less messily
 * with easier functionality to implement new events */ 
class Controller {
	private:
		std::vector<ControllerCommand<Point, PointDelta>*> commands;
		Configuration configuration;
		Point* myPoint;
	public:
		Controller(Configuration config) {
			this->configuration = config;
			this->myPoint = new Point(50, 50);			
			
			this->commands.push_back(new ControllerCommand<Point, PointDelta>( [](Point* p, PointDelta g) { (*p) += g;}, this->myPoint));
		}
		
		~Controller() {}
		
		bool handleEvents() {
			return true;
		}
};
