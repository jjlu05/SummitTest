//
// GameWin.cpp
//

// Engine includes.
#include "EventStep.h"
#include "GameManager.h"
#include "LogManager.h"
#include "ResourceManager.h"
#include "WorldManager.h"
#include "Vector.h"

// Game includes.
#include "GameWin.h"
#include "GameStart.h"

GameWin::GameWin() {

    setType("GameWin");

    // Link to "message" sprite.
    if (setSprite("win1") == 0)
        time_to_live = getAnimation().getSprite()->getFrameCount() * 10;
    else
        time_to_live = 0;

    // Put in center of window.
    setPosition(df::Vector(50, 50));

    // Register for step event.
#ifdef DF_REGISTER_INTEREST
    registerInterest(df::STEP_EVENT);
#endif

    // Play "game over" sound.
    df::Sound* p_sound = RM.getSound("win");
    p_sound->play();

}

// When done, game over so shut down.
GameWin::~GameWin() {
    WM.markForDelete(this);
    GM.setGameOver();
}

// Handle event.
// Return 0 if ignored, else 1.
int GameWin::eventHandler(const df::Event* p_e) {

    if (p_e->getType() == df::STEP_EVENT) {
        step();
        return 1;
    }

    // If get here, have ignored this event.
    return 0;
}

// Count down to end of message.
void GameWin::step() {
    time_to_live--;
    if (time_to_live <= 0) {
        WM.markForDelete(this);
    }
}

// Override default draw so as not to display "value".
int GameWin::draw() {
    df::Object::draw();
    return 0;
}
