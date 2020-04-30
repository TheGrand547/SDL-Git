#include "GameInstance.h"
#define plusOrMinusOne(i) int i = -1; i <= 1; i++
typedef std::shared_ptr<ThingBase> ThingPtr;

namespace TEMPTEMP {
	std::vector<Line> LINES;
}

bool compare::operator()(const ThingBase* lhs, const ThingBase* rhs) const {
	if (lhs->originDistance() < rhs->originDistance()) {
		return true;
	}
	if (lhs->originDistance() > rhs->originDistance()) {
		return false;
	}
	return lhs < rhs;
}

GameInstance::GameInstance(SDL_Renderer* renderer, BoundedPoint offset) : offset(offset), playableArea(0, 0, Screen::MAX_WIDTH, Screen::MAX_HEIGHT), 
							renderer(renderer), collision(this) {}

GameInstance::~GameInstance() {}

void GameInstance::addThing(ThingPtr thing) {
	this->allThings.push_back(thing);
	thing->setParent(this);
	int flags = thing->getAbsoluteFlags();
	if (flags & DRAW) {
		this->drawThings.push_back(thing);
		if (!this->drawOrder.insert(thing.get()).second) {
			// TOOD: Log duplicate instance
		}
	}
	if (flags & SOLID) {
		this->collisionThings.push_back(thing);
		if (!(flags & MOVEABLE)) {
			//std::cout << "This thing shouldn't move" << std::endl;
		}
	}
	if (flags & MOVEABLE) {
		this->movingThings.push_back(thing);
	}
}

void GameInstance::update() {
	for (ThingPtr& thing: this->movingThings) {
		Point position = thing->getPosition();
		thing->update();
		if (position != thing->getPosition()) {
			this->drawOrder.erase(thing.get());
			this->drawOrder.insert(thing.get());
		}
	}
}

void GameInstance::draw() {
	for (ThingBase* thing: this->drawOrder) {
		thing->draw(this->renderer, this->offset);
	} 
	this->nodes.drawGroup();
	uint8_t t = 0;
	for (Line l: TEMPTEMP::LINES) {
		t++;
		l.setColor(t, 0x00, 0x00, 0xFF);
		l.drawLine(this->renderer, this->offset);
	}
}

Rect GameInstance::getPlayableArea() const {
	return this->playableArea;
}

SDL_Renderer* GameInstance::getRenderer() {
	return this->renderer;
}

Point& GameInstance::getOffset() {
	return this->offset;
}

void GameInstance::addNode(Point position, std::string data) {
	if (this->nodes.addNodeAt(position, data)) {
		LOG("Failure Placing Node at (%.1f, %.1f)", position.x(), position.y());
	}
}

void GameInstance::instanceBegin() {
	// Do final things before playing starts
	std::vector<Point> p;
	//std::vector<Line> LINES;
	//std::cout << this->allThings.size() << std::endl;
	for (const ThingPtr& thing: this->allThings) {
		//thing->addNodes();
		thing->gimme(p);
	}
	double AVG = 0;
	int NUMS = 0;
	for (Point f: p) { // First
		for (Point s: p) { // Second
			if (&f == &s) continue;
			//bool gfe = false;
			NUMS++;
			int count = 0;
			for (plusOrMinusOne(x1)) {
				for (plusOrMinusOne(x2)) {
					for (plusOrMinusOne(y1)) {
						for (plusOrMinusOne(y2)) {
							Line tempLine(f + Point(x1, y2), s + Point(x2, y2));
							if (this->collision.doesNotCollideWith(tempLine)) {
								count++;
							}
						}
					}
				}
			}
			AVG += count;
			if (count >= 8) {
				TEMPTEMP::LINES.push_back(Line(f, s));
			} 
		}
	}
	LOG("%f", (AVG / NUMS));
	std::cout << TEMPTEMP::LINES.size() << std::endl;
	for (Line f: TEMPTEMP::LINES) { // First
		for (Line s: TEMPTEMP::LINES) { // Second
			if (&f == &s) continue;
			if (f.shareNoPoints(s)) {
				Line a(f.getOrigin(), s.getOrigin());
				Line b(f.getEnd(), s.getEnd());
				if (this->collision.doesNotCollideWith(a) && this->collision.doesNotCollideWith(b)) {
					
					this->addNode(a.getOrigin(), "");
					this->addNode(a.getEnd(), "");
					//this->addNode(a.midPoint(), "");
					this->addNode(b.getOrigin(), "");
					this->addNode(b.getEnd(), "");
				}
			}
		}
	}
	Rect g(5, 5,5 ,5);
	LOG("Size: %i", this->nodes.size());
	//this->nodes.connectNodes();
	//this->nodes.purge();
}
