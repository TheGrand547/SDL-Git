#ifndef FOLLOWING_TEXT_H
#define FOLLOWING_TEXT_H
#include "Text.h"

// TODO: Implement
class FollowingText : public Text {
	protected:
		Point& position;
	public:
		FollowingText(Point& point);
		~FollowingText();
};
#endif
