#pragma once
#ifndef HEADERS_H
#define HEADERS_H
// Remove for alpha/beta/final releases
//#define NDEBUG 
#include "AlertTextHandler.h"
#include "Dot.h"
#include "essential/Configuration.h"
#include "essential/log.h"
#include "essential/random.h"
#include "essential/util.h"
#include "game_entities/BackgroundElement.h"
#include "game_entities/BackgroundGroup.h"
#include "game_entities/BadTest.h"
#include "game_entities/base/CollideBase.h"
#include "game_entities/BigWall.h"
#include "game_entities/DrawGroup.h"
#include "game_entities/SectorGroup.h"
#include "game_entities/SectorPath.h"
#include "game_entities/SectorPathFollower.h"
#include "GameInstance.h"
#include "MyBase.h"
#include "primitives/Line.h"
#include "primitives/Point.h"
#include "primitives/PointDelta.h"
#include "primitives/Rect.h"
#include "primitives/Vector.h"
#include "wrappers/AlertText.h"
#include "wrappers/AppearingText.h"
#include "wrappers/control/Controller.h"
#include "wrappers/control/SimpleButtonCommand.h"
#include "wrappers/Font.h"
#include "wrappers/FpsText.h"
#include "wrappers/HeldKey.h"
#include "wrappers/SpriteSheet.h"
#include "wrappers/Texture.h"
#include "wrappers/Timer.h"
#include<iostream>
#include<math.h>
#include<memory>
#include<queue>
#include<SDL2/SDL.h>
#include<SDL2/SDL2_framerate.h>
#include<SDL2/SDL2_gfxPrimitives.h>
#include<SDL2/SDL2_rotozoom.h>
#include<SDL2/SDL_thread.h>
#include<SDL2_image/SDL_image.h>
#include<SDL2_ttf/SDL_ttf.h>
#include<sstream>
#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<vector>
#endif
