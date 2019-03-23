#pragma once
#include "Point.h"
#include "Rect.h"	
#include "Texture.h"
class Box {
	//Class for boxes
private:
	const float indent = .15;
	const float outdent = .10;
	Line inLineA, inLineB;
	Rect outerRect, innerRect;
	Texture mTexture;
public:
	Box(Point topLeft, Point bottomRight) {
		outerRect = Rect(topLeft, bottomRight);
		//This is going to get ugly
		Point inPointLeft = Point(topLeft.x() + (outerRect.getWidth() * indent),
							topLeft.y());
		Point inPointRight = Point(bottomRight.x() - (outerRect.getWidth() * indent), 
						bottomRight.y() - outerRect.getHeight() * outdent);
		innerRect = Rect(inPointLeft,inPointRight);
		innerRect.setColorChannels(0xFF, 0xFF, 0x00, 0xFF);
		inLineA = Line(outerRect.getBottomLeft(), innerRect.getBottomLeft());
		inLineB = Line(inPointRight, bottomRight);
	}
			
	void loadTexture(SDL_Renderer *renderer, string path="resources/taff.jpg") {
		mTexture.loadFromFile(path.c_str(), renderer, innerRect.getWidth(), innerRect.getHeight());
	}
		
	void draw(SDL_Renderer* renderer) {
		outerRect.draw(renderer);
		innerRect.draw(renderer);
		inLineA.drawLine(renderer);
		inLineB.drawLine(renderer);
		if (mTexture.isLoaded() == true) {
			mTexture.render(innerRect.getTopLeft().x(), innerRect.getTopLeft().y(), renderer);
		}
	}
	
	Point collideLine(Line ray) {
		return outerRect.collideLine(ray);
	}

};
