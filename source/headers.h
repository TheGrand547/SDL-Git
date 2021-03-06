#pragma once
#ifndef HEADERS_H
#define HEADERS_H
#include "essential/Configuration.h"
#include "essential/log.h"
#include "essential/MathUtils.h"
#include "essential/misc.h"
#include "essential/util.h"
#include "game_entities/BackgroundElement.h"
#include "game_entities/BackgroundGroup.h"
#include "game_entities/BadTest.h"
#include "game_entities/BigWall.h"
#include "game_entities/DrawGroup.h"
#include "game_entities/FileStructureAnalyzer.h"
#include "game_entities/FootSteps.h"
#include "game_entities/SectorGroup.h"
#include "game_entities/SectorPath.h"
#include "game_entities/SectorPathFollower.h"
#include "primitives/Line.h"
#include "primitives/Point.h"
#include "primitives/Rect.h"
#include "primitives/Triangle.h"
#include "wrappers/AlertText.h"
#include "wrappers/AppearingText.h"
#include "wrappers/Controller.h"
#include "wrappers/Font.h"
#include "wrappers/FpsText.h"
#include "wrappers/HeldKey.h"
#include "wrappers/LinkedText.h"
#include "wrappers/SpriteSheet.h"
#include "wrappers/Surface.h"
#include "wrappers/Texture.h"
#include "wrappers/Timer.h"
#include "Color.h"
#include "Dot.h"
#include "GameInstance.h"
#include "TextHandler.h"
#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <ctime>
#include <iostream>
#include <memory>
#include <queue>
#include <SDL.h>
#include <SDL_thread.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <SDL2_framerate.h>
#include <SDL2_gfxPrimitives.h>
#include <SDL2_rotozoom.h>
#include <sstream>
#include <vector>
#endif
