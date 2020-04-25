#include "GameInstance.h"
typedef std::shared_ptr<ThingBase> ThingPtr;

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
		LOG("Success (%f,%f)", position.x(), position.y());
	}
}

void GameInstance::instanceBegin() {
	// Do final things before playing starts
	std::vector<Line> p;
	std::cout << this->allThings.size() << std::endl;
	for (const ThingPtr& thing: this->allThings) {
		//thing->addNodes();
		thing->gimme(p);
	}
	for (Line f: p) { // First
		for (Line s: p) { // Second
			if (&f == &s) continue;
			if (f.shareNoPoints(s)) {
				Line a(f.getOrigin(), s.getOrigin());
				Line b(f.getEnd(), s.getEnd());
				if (this->collision.doesNotCollideWith(a) && this->collision.doesNotCollideWith(b)) {
					this->addNode(a.getOrigin(), "");
					this->addNode(a.getEnd(), "");
					this->addNode(a.midPoint(), "");
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
