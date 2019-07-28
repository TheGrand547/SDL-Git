#pragma once
#include<SDL2/SDL.h>
#include "../../essential/constants.h"
#include "../../wrappers/Texture.h"
#include "CollideBase.h"
#include "../CollideBaseGroup.h"
#include "../../Dot.h"
#include "../NodeDrawGroup.h"
#include<vector>
#include<math.h>

class EnemyBase {
	protected:
		Texture* texture;
		Point position;
		int width = 50;
		int height = 50;
		float angle = 0;
		/* Experimental - Maybe remove this in favor of a pointer to its container? */
		CollideBaseGroup collide;
		NodeDrawGroup nav;
	public:
		EnemyBase(Point position = Point(0, 0));
		virtual ~EnemyBase();
		virtual void update() = 0;
		virtual void draw(Dot* dot);
		void setCollision(CollideBaseGroup& collide);
		void setNavigation(NodeDrawGroup& nav);
		void operator+=(Point delta);
		virtual bool checkLocationValidity() = 0;
		friend std::ostream& operator<<(std::ostream &output, const EnemyBase& base);
};
