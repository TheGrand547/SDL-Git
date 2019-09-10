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
#include<vector>
#include<math.h>
class EnemyBase;
#include "../ai/AiBrain.h"
#include "../EnemyDrawGroup.h"
#include "../ai/AiProng.h"
#include "../ai/AiBrain.h"

class EnemyBase {
	protected:
		Texture* texture;
		Timer timer, pathTimer;
		Point position;
		int width = 50;
		int height = 50;
		float angle = 0;
		int countedFrames = 0;
		
		NodePath path;
		EnemyDrawGroup* parent;
	public:
		EnemyBase(EnemyDrawGroup* parent, Point position = Point(0, 0));
		virtual ~EnemyBase();
		virtual void update() = 0;
		virtual void draw(SDL_Renderer* renderer, BoundedPoint& offset);
		Node* getClosestUnblockedNode();
		virtual Point getCenter() = 0;
		virtual Point getPos() = 0;
		void setParent(EnemyDrawGroup* parent);
		void operator+=(Point delta);
		void move(Point delta);
		virtual bool isLocationInvalid() = 0;
		friend std::ostream& operator<<(std::ostream& output, const EnemyBase& base);
		friend class AiProng;
};
