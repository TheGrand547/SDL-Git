#pragma once
#include "../../essential/constants.h"
#include "../../primitives/Vector.h"
#include "../../wrappers/Texture.h"
#include "../../wrappers/Timer.h"
#include "../../Dot.h"
#include "../NodeDrawGroup.h"
#include "../NodePath.h"
#include "EntityBase.h"
#include<math.h>
#include<memory>
#include<SDL2/SDL.h>
#include<vector>

class EnemyBase : public EntityBase {
	protected:
		Texture texture;
		Timer pathTimer;
		Point position;
		int width = 50;
		int height = 50;
		float angle = 0;
		bool turning = false;
		NodePath path;
	public:
		EnemyBase(Point position = Point(0, 0));
		virtual ~EnemyBase();
		virtual bool isLocationInvalid() const = 0;
		virtual Point getCenter() const = 0;
		virtual void update() = 0;
		virtual void draw(SDL_Renderer* renderer, Point offset = Point(0, 0));
		virtual void move();
		void turn(float delta);
		void toggleTurn();
		float getAngle() const;
		std::shared_ptr<Node> getClosestUnblockedNode();
		PointDelta pathFindTo(Point pos = Point());
		friend std::ostream& operator<<(std::ostream& output, const EnemyBase& base);
};
