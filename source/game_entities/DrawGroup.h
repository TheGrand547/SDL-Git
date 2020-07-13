#pragma once
#ifndef DRAW_GROUP_H
#define DRAW_GROUP_H

class GameInstance;

/* Base class for the various lists of entities or "things" that need to be drawn, updated, or otherwise 
 * be intereacted with as a group */
class DrawGroup {
	public:
		GameInstance* parent;
		DrawGroup(GameInstance* parent) : parent(parent) {}
		virtual ~DrawGroup() {}
		virtual bool exists() = 0;
		virtual int size() = 0;
		virtual void clearGroup() = 0;
		virtual void drawGroup() = 0;
};
#endif
