#pragma once
#include<SDL2/SDL.h>
#include "../../essential/constants.h"
#include "../../wrappers/Texture.h"
#include "../../wrappers/Timer.h"
#include "CollideBase.h"
#include "../CollideBaseGroup.h"
#include "../../Dot.h"
#include "../NodeDrawGroup.h"
#include<vector>
#include<math.h>
class EnemyBase;
#include "../EnemyDrawGroup.h"

class EnemyBase {
	protected:
		Texture* texture;
		Timer timer;
		Point position;
		int width = 50;
		int height = 50;
		float angle = 0;
		int countedFrames = 0;
		
		EnemyDrawGroup* parent;
	public:
		EnemyBase(EnemyDrawGroup* parent, Point position = Point(0, 0));
		virtual ~EnemyBase();
		virtual void update() = 0;
		virtual void draw(Dot* dot);
		void setParent(EnemyDrawGroup* parent);
		void operator+=(Point delta);
		void move(Point delta);
		virtual bool isLocationInvalid() = 0;
		friend std::ostream& operator<<(std::ostream& output, const EnemyBase& base);
};
