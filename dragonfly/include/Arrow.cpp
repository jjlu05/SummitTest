#include "Arrow.h"
#include "Explosion.h"

#include "WorldManager.h"
#include "EventOut.h"
#include "EventStep.h"

Arrow::Arrow(df::Vector skel_pos) {
	setType("Arrow");
	setSprite("arrow");
	setSolidness(df::SOFT);

	df::Vector p(skel_pos.getX() + 3, skel_pos.getY());
	setPosition(p);

	death_timer = 300;
}

Arrow::~Arrow() {
	Explosion* explo = new Explosion;
	explo->setPosition(getPosition());
}

int Arrow::eventHandler(const df::Event* p_e) {

	if (p_e->getType() == df::OUT_EVENT) {
		out();
		return 1;
	}
	if (p_e->getType() == df::COLLISION_EVENT) {
		const df::EventCollision* p_collision_event = dynamic_cast <df::EventCollision const*> (p_e);
		hit(p_collision_event);
		return 1;
	}
	if (p_e->getType() == df::STEP_EVENT) {
		step();
		return 1;
	}

	return 0;
}

void Arrow::hit(const df::EventCollision* p_collision_event) {
	if (((p_collision_event->getObject1()->getType()) == "Hero") ||
		((p_collision_event->getObject2()->getType()) == "Hero")) {
		WM.markForDelete(p_collision_event->getObject1());
		WM.markForDelete(p_collision_event->getObject2());
	}

	if (((p_collision_event->getObject1()->getType()) == "Wall") ||
		((p_collision_event->getObject2()->getType()) == "Wall")) {
		WM.markForDelete(this);
	}

	if (((p_collision_event->getObject1()->getType()) == "Ground") ||
		((p_collision_event->getObject2()->getType()) == "Ground")) {
		WM.markForDelete(this);
	}
}

void Arrow::out() {
	WM.markForDelete(this);
}

void Arrow::step() {
	death_timer--;

	if (death_timer <= 0) {
		WM.markForDelete(this);
	}
}
