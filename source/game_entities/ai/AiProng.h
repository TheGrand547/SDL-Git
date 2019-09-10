#pragma once
#ifndef AI_PRONG_H
#define AI_PRONG_H
class AiProng;
#include "../base/EnemyBase.h"
#include "../../primitives/Vector.h"
#include "../../essential/constants.h"

class AiProng {
	/* Badly named but single "stem" of an AI that (can) take orders from a higher AI controller */
	public: // Also kind of annoying to have public before private, look to see if there is a way around it
		// Find a way to put this back here 
		enum TYPE { 
			PATHFIND_TO_TARGET
		};
		AiProng(TYPE myType);
		~AiProng();
		void execute(EnemyBase* target);
		void pathFindTo(EnemyBase* actor);
	private:
		TYPE myType;
};
#endif
