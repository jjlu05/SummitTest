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

Wall::Wall(){

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
int Wall::eventHandler(const df::Event* p_e) {

    if (p_e->getType() == df::COLLISION_EVENT) {
        const df::EventCollision* p_collision_event = dynamic_cast <df::EventCollision const*> (p_e);
        hit(p_collision_event);
        return 1;
    }




    // If get here, have ignored this event.
    return 0;
}

// Called with Saucer collides.
void Wall::hit(const df::EventCollision* p_collision_event) {



}

