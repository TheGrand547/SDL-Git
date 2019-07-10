#include "BadTest.h"

BadTest::BadTest(Point position) : EnemyBase(position) {
	this->c = new PathManager<EnemyBase>(this);
	/*
	this->c->AddPath(new LinePath<EnemyBase>(Point(200, -200), toTicks(1)));
	this->c->AddPath(new CirclePath<EnemyBase>(40, 1, Path<Point>::SINGLE_LOOP, false));
	this->c->AddPath(new LinePath<EnemyBase>(Point(-200, 200), toTicks(1)));
	this->c->AddPath(new CirclePath<EnemyBase>(40, 1, Path<Point>::SINGLE_LOOP, false));			
	this->c->setRepeat(true);
	*/
}

BadTest::BadTest(const BadTest& that) : EnemyBase(that.position) {
	*this = BadTest(that.position);
}

BadTest::~BadTest() {
	delete this->c;
}

void BadTest::set() {
	this->texture->createBlank(MegaBase::renderer, 50, 50, 0xFF0000FF);
}

void BadTest::render(Dot* dot) {
	if (this->texture->isLoaded()) {
		this->texture->setPos(this->position);
		this->texture->render(MegaBase::renderer, MegaBase::offset);
	}
	
	// "AI" - also -> TODO: clean up this dumpster fire
	if (this->nav != NULL) {
		Point center = this->position + Point() + Point(this->width / 2, this->height / 2);
		std::vector<Node*> temp;
		for (int i = 0; i < this->nav->size(); i++) {
			if (checkCollisionBetweenLineAndGroup(Line(center, (*this->nav)[i]->getPosition()), this->collide)) {
				temp.push_back((*this->nav)[i]);
			}
		}
		// Find closest one
		Node* closest = temp[0];
		if (temp.size() > 1) {
			for (int i = 1; i < temp.size(); i++) {
				if (temp[i]->getPosition().distanceToPoint(center) < closest->getPosition().distanceToPoint(center)) {
					closest = temp[i];
				}
			}
		}
		if (closest->getPosition().distanceToPoint(center) < 5 || this->running) {
			if (this->running) {
				if (this->stored == NULL || (closest->getPosition().distanceToPoint(center) < 5 && this->stored == closest)) {
					this->stored = closest->randomConnectedNode();
				}
				closest = this->stored;
			} else {
				this->running = true;
			}
		} 
		float ange = atan2(closest->getPosition().y() - center.y(), closest->getPosition().x() - center.x());
		*this += Point(1 * cos(ange), 1 * sin(ange));
	}
	/*
	Point center = this->position + Point() + Point(this->width / 2, this->height / 2);
	float ange = atan2(dot->getCenter().y() - center.y(), dot->getCenter().x() - center.x());
	if (std::abs(ange - this->angle) < M_PI_2) {
		bool flag = false;
		for (int i = -20; i <= 20; i++) {
			Point pTemp = Point(center);
			pTemp += Point(300 * cos(this->angle + radians(i)), 300 * sin(this->angle + radians(i)));
			Line temp = Line(center, pTemp);
			Point newTemp = dot->getRect().collideLine(temp);
			if (newTemp.isReal()) {
				if (!flag && center.distanceToPoint(newTemp) > 50) {
					// *this += Point(2 * cos(this->angle + radians(i)), 2 * sin(this->angle + radians(i)));
					flag = !flag;
				}
				Line newTempLine = Line(center, newTemp);
				newTempLine.setColorChannels(COLORS::CYAN);
				newTempLine.drawLine(MegaBase::renderer, MegaBase::offset);
				continue;
			}
			temp.setColorChannels(COLORS::BLACK);
			temp.drawLine(MegaBase::renderer, MegaBase::offset);
		}
	}*/
}

void BadTest::update() {
	if (!this->texture->isLoaded()) {
		this->set();
	}
	this->c->update();
}

Point BadTest::getPos() {
	return this->position;
}
