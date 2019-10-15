#pragma once
#include<SDL2/SDL.h>
#include "../../essential/constants.h"
#include "../../wrappers/Texture.h"
#include "../../wrappers/Timer.h"
#include "CollideBase.h"
#include "../CollideBaseGroup.h"
#include "../../Dot.h"
#include "../NodeDrawGroup.h"
#include "../NodePath.h"
#include "../../primitives/Vector.h"
#include "EntityBase.h"
#include<vector>
#include<math.h>
#include<memory>
class EnemyBase;
#include "../EnemyDrawGroup.h"

class EnemyBase : public EntityBase {
	protected:
		Texture texture;
		Timer standardTimer, pathTimer;
		Point position;
		int width = 50;
		int height = 50;
		float angle = 0;
		
		NodePath path;
		EnemyDrawGroup* parent;
	public:
		EnemyBase(EnemyDrawGroup* parent, Point position = Point(0, 0));
		virtual ~EnemyBase();
		virtual bool isLocationInvalid() = 0;
		virtual Point getCenter() = 0;
		virtual Point getPos() = 0;
		virtual void update() = 0;
		virtual void draw(SDL_Renderer* renderer, BoundedPoint& offset);
		Node* getClosestUnblockedNode();
		void setParent(EnemyDrawGroup* parent);
		void move();
		void pathFindTo(Point pos = Point());
		friend std::ostream& operator<<(std::ostream& output, const EnemyBase& base);
};
