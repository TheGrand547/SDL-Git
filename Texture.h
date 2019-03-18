#pragma once
typedef Uint8 uint8_t;
class Texture {
private:
	int *width, *height;
	int *xpos, *ypos;
	SDL_Texture *texture;
public:
	Texture() {
		texture = NULL;
		width = new int(0);
		height = new int(0);
		xpos = new int(0);
		ypos = new int(0);
	}
	
	void loadFromFile(string path, SDL_Renderer* renderer, int xSize = 0, int ySize = 0, Uint8 r = 0xFF, Uint8 g = 0xFF, Uint8 b = 0xFF);
	
	~Texture() {
		free();
		delete this->width;
		delete this->height;
		delete this->xpos;
		delete this->ypos;
	}
	
	Texture &operator=(const Texture &that) {
		width = new int(0);
		height = new int(0);
		xpos = new int(0);
		ypos = new int(0);
		*height = *(that.height);
		*width = *(that.width);
		*xpos = *(that.xpos);
		*ypos = *(that.ypos);
		texture = NULL;
		loadFromFile("Taff.jpg", gRenderer, 100, 50);
	}
	
	Texture (const Texture &that) {
		width = new int(0);
		height = new int(0);
		xpos = new int(0);
		ypos = new int(0);
		*height = *(that.height);
		*width = *(that.width);
		*xpos = *(that.xpos);
		*ypos = *(that.ypos);
		texture = NULL;
		loadFromFile("Taff.jpg", gRenderer, 100, 50);
	}
	
	void free() {
		if (texture != NULL) {
			SDL_DestroyTexture(texture);
			texture = NULL;	
		}
	}
	
	SDL_Surface* scaleToCoords(SDL_Surface *surf, float desiredWidth, float desiredHeight) {
		double xFactor = desiredWidth / surf->w;
		double yFactor = desiredHeight / surf->h;
		return rotozoomSurfaceXY(surf, 0, xFactor, yFactor, 1);
	}
	
	void setColor(Uint8 red, Uint8 green, Uint8 blue) {
		SDL_SetTextureColorMod(this->texture, red, green, blue);
	}
	
	void setAlpha(Uint8 alpha) {
		SDL_SetTextureAlphaMod(this->texture, alpha);
	}
	
	void render(int x, int y, SDL_Renderer *renderer, SDL_Rect* clip=NULL, double angle=0, 
				SDL_Point* center=NULL, SDL_RendererFlip flip = SDL_FLIP_NONE) {
		SDL_Rect renderQuad = {x, y, *width, *height};
		if( clip != NULL ) {
			renderQuad.w = clip->w;
			renderQuad.h = clip->h;
		}
		SDL_RenderCopyEx(renderer, texture, clip, &renderQuad, angle, center, flip);
	}
	
	void render(SDL_Renderer *renderer, SDL_Rect* clip=NULL, double angle=0, 
				SDL_Point* center=NULL, SDL_RendererFlip flip = SDL_FLIP_NONE) {
		render(*(this->xpos), *(this->ypos), renderer, clip, angle, center, flip);
	}
	
	bool isLoaded() {
		return texture != NULL;
	}
	
	void createBlank(SDL_Renderer *renderer, int w, int h, uint32_t color) {
		free();
		SDL_Texture *tempText = NULL;
		SDL_Surface *tempSurf = SDL_CreateRGBSurface(0, w, h, 32, 0, 0, 0, 0);
		if (tempSurf != NULL) {
			SDL_FillRect(tempSurf, NULL, color);
			tempText = SDL_CreateTextureFromSurface(renderer, tempSurf);
			*width = tempSurf->w;
			*height = tempSurf->h;
		
			texture = tempText;
		}
		SDL_FreeSurface(tempSurf);
	}
	
	void setPos(int x = 0, int y = 0) {
		*(this->xpos) = x;
		*(this->ypos) = y;
	}
	
	void setPos(Point point) {
		*(this->xpos) = point.x();
		*(this->ypos) = point.y();
	}
	
	void setPos(Point *point) {
		*(this->xpos) = point->x();
		*(this->ypos) = point->y();
	}
	
};

void Texture::loadFromFile(string path, SDL_Renderer* renderer, int xSize, int ySize, Uint8 r, Uint8 g, Uint8 b) {
		free();
		SDL_Texture *newTexture = NULL;
		SDL_Surface *tempSurface = IMG_Load(path.c_str());
		if (tempSurface == NULL) {
			printf("Unable to load image %s! SDL_image Error: %s\n", path.c_str(), IMG_GetError());
		} else {
			SDL_SetColorKey(tempSurface, SDL_TRUE, SDL_MapRGB( tempSurface->format, r, g, b));
			if (xSize > 0 && ySize > 0) {
				tempSurface = scaleToCoords(tempSurface, xSize, ySize);
			}
			newTexture = SDL_CreateTextureFromSurface(renderer, tempSurface);
			if (newTexture == NULL) {
				printf( "Unable to create texture from %s! SDL Error: %s\n", path.c_str(), SDL_GetError() );
			} else {
				*width = tempSurface->w;
				*height = tempSurface->h;
			}
		}
		SDL_FreeSurface(tempSurface);
		texture = newTexture;
	}
