#pragma once
#include<SDL2/SDL.h>
#include<SDL2/SDL2_gfxPrimitives.h>
#include<SDL2_ttf/SDL_ttf.h>
#include<SDL2_image/SDL_image.h>
#include<vector>
#include "CollideBase.h"
#include "PointDelta.h"

class Screen {
	//Class that holds all the information and runtime stuff for a single screen of the game
	private:
		static const int CAMERA_WIDTH = 640;
		static const int CAMERA_HEIGHT = 480;
		int levelSizeX, levelSizeY;
		int cameraPosX, cameraPosY;
		std::vector<CollideBase>* objects;
		
	public:
		Screen() {
		}
		
		~Screen() {
			delete this->objects;
		}
		
		void correctPostion() {
			if (this->cameraPosX > this->levelSizeX - CAMERA_WIDTH) {
				//If the camera is too far right, make it not too far right
				this->cameraPosX = this->levelSizeX - CAMERA_WIDTH;
			}
			if (this->cameraPosY > this->levelSizeY - CAMERA_HEIGHT) {
				this->cameraPosY = this->levelSizeY - CAMERA_HEIGHT;
			}
			if (this->cameraPosX < 0) {
				this->cameraPosX = 0;
			}
			if (this->cameraPosY < 0) {
				this->cameraPosY = 0;
			}
		}
		
		void run(SDL_Renderer* renderer) {
			//Runs a single frame of the level, done this way because hopefull it'll be more efficent
			
		}
		
};
