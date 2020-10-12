// Testing file ONLY
#include <SDL2/SDL.h>
#include "LinkedList.h"
#include <vector>

void main() {
	const int TIMES = 10000;
	const int ELEMS = 1000;
	auto star = SDL_GetTicks();
	for (int _i = 0; _i < TIMES; _i++) {
		LinkedList<int> lis;
		for (int i = 0; i < ELEMS; i++) {
			lis.push_back(i);
		}
		for (int i = 0; i < ELEMS / 2; i++) {
			lis.erase(lis.begin());
		}
		for (int i = 0; i < ELEMS; i++) {
			lis.push_back(i);
		}
		for (int i = 0; i < ELEMS / 2; i++) {
			lis.erase(lis.begin());
		}
	}
	std::cout << "Time: " << unsigned (SDL_GetTicks() - star) << std::endl;
	star = SDL_GetTicks();
	for (int _i = 0; _i < TIMES; _i++) {
		std::vector<int> lis;
		for (int i = 0; i < ELEMS; i++) {
			lis.push_back(i);
		}
		for (int i = 0; i < ELEMS / 2; i++) {
			lis.erase(lis.begin());
		}
		for (int i = 0; i < ELEMS; i++) {
			lis.push_back(i);
		}
		for (int i = 0; i < ELEMS / 2; i++) {
			lis.erase(lis.begin());
		}
	}
	std::cout << "Time: " << unsigned (SDL_GetTicks() - star) << std::endl;
}
