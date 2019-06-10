#pragma once
#ifndef HEADERS_H
#define HEADERS_H
#include<iostream>
#include<math.h>
#include<SDL2/SDL.h>
#include<SDL2_image/SDL_image.h>
#include<SDL2/SDL2_gfxPrimitives.h>
#include<SDL2/SDL2_rotozoom.h>
#include<SDL2/SDL2_framerate.h>
#include<SDL2_ttf/SDL_ttf.h>
#include<SDL2/SDL_thread.h>
#include<stdio.h>
#include<sstream>
#include<vector>
#include "game_entities/Box.h"
#include "game_entities/BackgroundElement.h"
#include "primitives/Line.h"
#include "primitives/Point.h"
#include "wrappers/Font.h"
#include "primitives/Rect.h"
#include "wrappers/Timer.h"
#include "wrappers/Texture.h"
#include "essential/util.h"
#include "essential/random.h"
#include "MyBase.h"
#include "Dot.h"
#include "primitives/PointDelta.h"
#include "wrappers/HeldKey.h"
#include "game_entities/base/CollideBase.h"
#include "essential/Configuration.h"
#include "game_entities/BadTest.h"
#include "wrappers/control/Controller.h"
#include "wrappers/AppearingText.h"
#include "wrappers/FpsText.h"
#include "game_entities/DrawGroup.h"
#include "game_entities/CollideBaseGroup.h"
#include "game_entities/BackgroundGroup.h"
#include "game_entities/CollideBaseFactory.h"
#include "game_entities/EnemyDrawGroup.h"
#endif
