#include "../../primitives/Point.h"

namespace BASIC {
	auto constexpr PLAYER_UP_KEYDOWN = [](Point* p) {p->y -= 1;};
	auto constexpr PLAYER_UP_KEYUP = [](Point* p) {if (p->y < 0) {p->y = 0;}};
	
	auto constexpr PLAYER_DOWN_KEYDOWN = [](Point* p) {p->y += 1;};
	auto constexpr PLAYER_DOWN_KEYUP = [](Point* p) {if (p->y > 0) {p->y = 0;}};
	
	auto constexpr PLAYER_RIGHT_KEYDOWN = [](Point* p) {p->x += 1;};
	auto constexpr PLAYER_RIGHT_KEYUP = [](Point* p) {if (p->x > 0) {p->x = 0;}};
	
	auto constexpr PLAYER_LEFT_KEYDOWN = [](Point* p) {p->x -= 1;};
	auto constexpr PLAYER_LEFT_KEYUP = [](Point* p) {if (p->x < 0) {p->x = 0;}};
}
