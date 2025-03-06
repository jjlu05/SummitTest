#include "Skeleton.h"
#include "EventStep.h"
#include "Hero.h"
#include "Box.h"
#include "Arrow.h"

#include "WorldManager.h"
#include <cmath>

Skeleton::Skeleton(Hero* a_hero) {
	df::Vector corner = getBox().getCorner();
	corner.scale(5);
	attack_range.setCorner(corner);
	attack_range.setHorizontal(getBox().getHorizontal() * 5);
	attack_range.setVertical(getBox().getVertical() * 5);

	setType("Skeleton");
	setSprite("skeleton");

	p_hero = a_hero;

	attack_slowdown = 50;
	attack_cooldown = attack_slowdown;

}

int Skeleton::eventHandler(const df::Event* p_e) {

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

void Skeleton::step() {
	df::Vector corner = getBox().getCorner();
	corner.scale(5);
	attack_range.setCorner(corner);
	attack_cooldown--;

	df::Vector distance = df::Vector(getPosition().getX() - p_hero->getPosition().getX(),
		getPosition().getY() - p_hero->getPosition().getY());

	if (std::abs(distance.getMagnitude()) <= 50) {
		if (attack_cooldown <= 0) {
			attack();
			attack_cooldown = attack_slowdown;
		}
	}
}

void Skeleton::hit(const df::EventCollision* p_collision_event) {

	//Collision with player
	if (((p_collision_event->getObject1()->getType()) == "Hero") ||
		((p_collision_event->getObject2()->getType()) == "Hero")) {
		WM.markForDelete(p_collision_event->getObject1());
		WM.markForDelete(p_collision_event->getObject2());
	}
}

void Skeleton::attack() {
	df::Vector v = df::Vector(p_hero->getPosition().getX() - getPosition().getX(), p_hero->getPosition().getY() - getPosition().getY());
	v.normalize();
	v.scale(0.75);

	Arrow* arrow = new Arrow(getPosition());
	arrow->setVelocity(v);
}

