#include "Mole.h"

#include "WorldManager.h"
#include "EventStep.h"
#include "ObjectList.h"
#include "Vector.h"
#include "EventOut.h"
#include "Hero.h"

Mole::Mole() {
	setType("Mole");
	setSprite("mole");
	grounded = false;
	ledge_found = false;

	df::Vector v(getPosition().getX(), getPosition().getY() + 1.33);
	df::ObjectList collisions = WM.getCollisions(this, v);

	if ((!grounded) && (!collisions.isEmpty()) && (collisions[0]->getType() == "Ground")) {
		grounded = true;
		ledge_found = true;
	}
}

int Mole::eventHandler(const df::Event* p_e) {

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

void Mole::step() {
	df::Vector v(getPosition().getX(), getPosition().getY() + 1.33);
	df::ObjectList collisions = WM.getCollisions(this, v);

	if ((!collisions.isEmpty()) && (collisions[0]->getType() == "Ground")) {
		grounded = true;
	}
	else {
		grounded = false;
	}

	if (!ledge_found) {
		setVelocity(df::Vector(0, getVelocity().getY() + 0.03));
	}

	if (!grounded && ledge_found) {
		df::Vector new_vel = getVelocity();
		new_vel.scale(-1);
		if (new_vel.getX() == -0.3) {
			setSprite("mole");
		}
		else {
			setSprite("mole-right");
		}
		setVelocity(new_vel);
	}
}

void Mole::hit(const df::EventCollision* p_collision_event) {
	df::EventOut ev1;

	if (p_collision_event->getObject1()->getType() == "Hero") {
		Hero* hero = dynamic_cast<Hero*>(p_collision_event->getObject1());

		if (hero->returnLives() > 0) {
			WM.onEvent(&ev1);
		}
	}
	else if (p_collision_event->getObject2()->getType() == "Hero") {
		Hero* hero = dynamic_cast<Hero*>(p_collision_event->getObject2());

		if (hero->returnLives() > 0) {
			WM.onEvent(&ev1);
		}
	}


	if (((p_collision_event->getObject1()->getType()) == "Ground") ||
		((p_collision_event->getObject2()->getType()) == "Ground")) {
		ledge_found = true;
		setVelocity(df::Vector(0.3, 0));
	}

	if (((p_collision_event->getObject1()->getType()) == "Wall") ||
		((p_collision_event->getObject2()->getType()) == "Wall")) {
		df::Vector new_vel = getVelocity();
		new_vel.scale(-1);
		setVelocity(new_vel);
	}

}

bool Mole::getGrounded() const {
	return grounded;
}
