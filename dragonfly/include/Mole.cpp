#include "Mole.h"
#include "WorldManager.h"
#include "EventStep.h"
#include "ObjectList.h"
#include "Vector.h"
#include "EventOut.h"
#include "Hero.h"

Mole::Mole() {
    setType("Mole");
    // Start with a sprite facing right.
    setSprite("mole-right");
    grounded = false;
    ledge_found = false;

    // Initial ground check beneath mole.
    df::Vector v(getPosition().getX(), getPosition().getY() + 1.33);
    df::ObjectList collisions = WM.getCollisions(this, v);
    if (!collisions.isEmpty() && collisions[0]->getType() == "Ground") {
        grounded = true;
        ledge_found = true;
    }
}

int Mole::eventHandler(const df::Event* p_e) {
    if (p_e->getType() == df::COLLISION_EVENT) {
        const df::EventCollision* p_collision_event = dynamic_cast<const df::EventCollision*>(p_e);
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
    // Check directly beneath the mole.
    df::Vector below(getPosition().getX(), getPosition().getY() + 1.33);
    df::ObjectList collisions = WM.getCollisions(this, below);
    if (!collisions.isEmpty() && collisions[0]->getType() == "Ground") {
        grounded = true;
    }
    else {
        grounded = false;
    }

    // If the mole has found a ledge already...
    if (ledge_found) {
        // If the mole is no longer grounded (i.e. at the edge), flip its horizontal direction.
        if (!grounded) {
            df::Vector currentVel = getVelocity();
            // Reverse the X component.
            currentVel.setX(-currentVel.getX());
            setVelocity(currentVel);
            // Update sprite based on new horizontal direction.
            if (currentVel.getX() > 0) {
                setSprite("mole-right");
            }
            else {
                setSprite("mole");
            }
        }
    }
    else {
        // If no ledge has been detected, apply gravity.
        df::Vector currentVel = getVelocity();
        currentVel.setY(currentVel.getY() + 0.03);
        setVelocity(currentVel);
    }
}

void Mole::hit(const df::EventCollision* p_collision_event) {
    df::EventOut ev1;

    // If the hero is hit, send an out event.
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

    // When colliding with the ground, assume a ledge was found.
    if (((p_collision_event->getObject1()->getType()) == "Ground") ||
        ((p_collision_event->getObject2()->getType()) == "Ground")) {
        ledge_found = true;
        // Set an initial horizontal velocity (to the right, for example).
        setVelocity(df::Vector(0.3, 0));
        setSprite("mole-right");
    }

    // Reverse direction on collision with a wall.
    if (((p_collision_event->getObject1()->getType()) == "Wall") ||
        ((p_collision_event->getObject2()->getType()) == "Wall")) {
        df::Vector new_vel = getVelocity();
        new_vel.setX(-new_vel.getX());
        setVelocity(new_vel);
        // Update sprite accordingly.
        if (new_vel.getX() > 0)
            setSprite("mole-right");
        else
            setSprite("mole");
    }
}

bool Mole::getGrounded() const {
    return grounded;
}
