#include "../../primitives/PointDelta.h"
#include "../../primitives/Point.h"

namespace BASIC {
	auto constexpr PLAYER_UP_KEYDOWN = [](PointDelta* p){*p -= p->getYPoint();};
	auto constexpr PLAYER_UP_KEYUP = [](PointDelta* p){if(p->y() < 0){p->yZero();}};
	
	auto constexpr PLAYER_DOWN_KEYDOWN = [](PointDelta* p){*p += p->getYPoint();};
	auto constexpr PLAYER_DOWN_KEYUP = [](PointDelta* p){if(p->y() > 0){p->yZero();}};
	
	auto constexpr PLAYER_RIGHT_KEYDOWN = [](PointDelta* p){*p += p->getXPoint();};
	auto constexpr PLAYER_RIGHT_KEYUP = [](PointDelta* p){if(p->x() > 0){p->xZero();}};
	
	auto constexpr PLAYER_LEFT_KEYDOWN = [](PointDelta* p){*p -= p->getXPoint();};
	auto constexpr PLAYER_LEFT_KEYUP = [](PointDelta* p){if(p->x() < 0){p->xZero();}};
}
