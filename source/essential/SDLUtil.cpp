#include "SDLUtil.h"

SDL_Surface* scaleToSize(SDL_Surface* surf, double desiredWidth, double desiredHeight) {
	if (!desiredWidth && !desiredHeight) {
		return surf;
	}
	double xFactor = desiredWidth / surf->w;
	double yFactor = desiredHeight / surf->h;
	return rotozoomSurfaceXY(surf, 0, xFactor, yFactor, 0);
}
