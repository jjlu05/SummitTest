//
// Saucer.cpp
//

// System includes.
#include <stdlib.h>		// for rand()

// Engine includes.
#include "EventCollision.h"
#include "EventNuke.h"
#include "EventOut.h"
#include "EventView.h"
#include "LogManager.h"
#include "ResourceManager.h"
#include "WorldManager.h"

// Game includes.
#include "Explosion.h"
#include "Points.h"
#include "Wall.h"
Wall::Wall(int num){
    id = num;
    // Setup "saucer" sprite.
    setSprite("wall");

    // Set object type.
setType("Wall");


    // Register interest in "nuke" event.
#ifdef DF_REGISTER_INTEREST
#endif
}


// Handle event.
// Return 0 if ignored, else 1.
int test = 0;
bool found = false;
int Wall::eventHandler(const df::Event* p_e) {

    if (p_e->getType() == df::COLLISION_EVENT) {
        const df::EventCollision* p_collision_event = dynamic_cast <df::EventCollision const*> (p_e);
        hit(p_collision_event);
        return 1;
    }

    if (p_e->getType() == df::STEP_EVENT) {
        for (int i = 0; i < WM.getAllObjects().getCount(); i++) {
        
            if (WM.getAllObjects()[i]->getType() == "Hero") {
                test = i;
                found = true;
            }
        }
        if (found) {
            if (id==1) {
                setPosition(df::Vector(0, WM.getAllObjects()[test]->getPosition().getY()));
            }
            if (id==2) {
                setPosition(df::Vector(238, WM.getAllObjects()[test]->getPosition().getY()));

            }
        }

        return 1;
    }


    // If get here, have ignored this event.
    return 0;
}

// Called with Saucer collides.
void Wall::hit(const df::EventCollision* p_collision_event) {



}

