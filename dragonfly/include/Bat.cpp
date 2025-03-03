#include "Bat.h"

#include "WorldManager.h"

Bat::Bat() {
	setType("Bat");
	setSprite("bat");

	setVelocity(df::Vector(-0.25, 0));
}

int Bat::eventHandler(const df::Event* p_e) {
	if (p_e->getType() == df::COLLISION_EVENT) {
		const df::EventCollision* p_collision_event = dynamic_cast <df::EventCollision const*> (p_e);
		hit(p_collision_event);
		return 1;
	}

	return 0;
}

void Bat::hit(const df::EventCollision* p_collision_event) {
	//Collision with wall
	if ((p_collision_event->getObject1()->getType() == "Wall") ||
		(p_collision_event->getObject2()->getType() == "Wall")) {
		df::Vector new_velocity = getVelocity();
		this->setVelocity(df::Vector(-this->getVelocity().getX(), this->getVelocity().getY()));
	
	}

	////Collision with player
	//if (((p_collision_event->getObject1()->getType()) == "Hero") ||
	//	((p_collision_event->getObject2()->getType()) == "Hero")) {
	//	WM.markForDelete(p_collision_event->getObject1());
	//	WM.markForDelete(p_collision_event->getObject2());
	//}
}