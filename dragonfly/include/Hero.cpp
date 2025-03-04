//
// Hero.cpp
//

// Engine includes.
#include "EventMouse.h"
#include "EventStep.h"
#include "EventView.h"
#include "GameManager.h"
#include "LogManager.h"
#include "ResourceManager.h"
#include "WorldManager.h"

// Game includes.
#include "Bullet.h"
#include "EventNuke.h"
#include "Explosion.h"
#include "GameOver.h"
#include "Hero.h"
#include "iostream"
bool grounded = false;
float x = 0;
float y = 0;
Hero::Hero() {

    // Link to "ship" sprite.
    setSprite("hero");

    // Player controls hero, so register for input events.
#ifdef DF_REGISTER_INTEREST
    registerInterest(df::KEYBOARD_EVENT);
    registerInterest(df::MSE_EVENT);

    // Need to update rate control each step.
    registerInterest(df::STEP_EVENT);
#endif

    // Set object type.
    setType("Hero");
    WM.setViewFollowing(this);  

    // Set starting location.
    df::Vector p(7, WM.getBoundary().getVertical() / 2);
    setPosition(p);

    // Create reticle for firing bullets.
    p_reticle = new Reticle();
    p_reticle->draw();

    // Set attributes that control actions.
    move_slowdown = 2;
    move_countdown = move_slowdown;
    fire_slowdown = 30;
    fire_countdown = fire_slowdown;
    nuke_count = 1;
    //WM.setViewFollowing(this);

}

Hero::~Hero() {

    // Create GameOver object.
    new GameOver;

    // Make big explosion.
    for (int i = -8; i <= 8; i += 5) {
        for (int j = -5; j <= 5; j += 3) {
            df::Vector temp_pos = this->getPosition();
            temp_pos.setX(this->getPosition().getX() + i);
            temp_pos.setY(this->getPosition().getY() + j);
            Explosion* p_explosion = new Explosion;
            p_explosion->setPosition(temp_pos);
        }
    }

    // Mark Reticle for deletion.
    WM.markForDelete(p_reticle);
}

// Handle event.
// Return 0 if ignored, else 1.
int Hero::eventHandler(const df::Event* p_e) {

    if (p_e->getType() == df::KEYBOARD_EVENT) {
        const df::EventKeyboard* p_keyboard_event = dynamic_cast <const df::EventKeyboard*> (p_e);
        kbd(p_keyboard_event);
        return 1;
    }

    if (p_e->getType() == df::MSE_EVENT) {
        LM.writeLog("MOUSE EVENT HAPPENED");
        const df::EventMouse* p_mouse_event = dynamic_cast <const df::EventMouse*> (p_e);
        mouse(p_mouse_event);
        return 1;
    }

    if (p_e->getType() == df::STEP_EVENT) {
        step();
        //grounded = false;

        return 1;
    }
    if (p_e->getType() == df::COLLISION_EVENT) {
        const df::EventCollision* p_collision_event = dynamic_cast <df::EventCollision const*> (p_e);
        if (((p_collision_event->getObject1()->getType()) == "Bat") ||
            ((p_collision_event->getObject2()->getType()) == "Bat")) 
        {

            this->setVelocity(df::Vector(1, -1));
        }
        if (((p_collision_event->getObject1()->getType()) == "Wall") ||
            ((p_collision_event->getObject2()->getType()) == "Wall"))
        {

            x = 0;
        }
        return 1;
    }

    // If get here, have ignored this event.
    return 0;
}

// Take appropriate action according to mouse action.
void Hero::mouse(const df::EventMouse* p_mouse_event) {
    // Pressed button?
    //if ((p_mouse_event->getMouseAction() == df::CLICKED)/* && (p_mouse_event->getMouseButton() == df::Mouse::LEFT)*/) {
    //    fire(p_mouse_event->getMousePosition());
    //}
}

// Track key states
bool holdingA = false;
bool holdingD = false;

// Take appropriate action according to key pressed.
void Hero::kbd(const df::EventKeyboard* p_keyboard_event) {
    WM.setViewPosition(this->getPosition());

    switch (p_keyboard_event->getKey()) {
    case df::Keyboard::A:
        if (p_keyboard_event->getKeyboardAction() == df::KEY_PRESSED) {
            std::cout << "A";
            holdingA = true;
            x = -0.3*2*1.5;
        }
        if (p_keyboard_event->getKeyboardAction() == df::KEY_RELEASED) {
            std::cout << "Aup";
            holdingA = false;
            if (!holdingD) x = 0;
        }
        break;

    case df::Keyboard::D:
        if (p_keyboard_event->getKeyboardAction() == df::KEY_PRESSED) {
            holdingD = true;
            x = 0.3*2*1.5;
        }
        if (p_keyboard_event->getKeyboardAction() == df::KEY_RELEASED) {
            holdingD = false;
            if (!holdingA) x = 0; 
        }
        break;

    case df::Keyboard::SPACE:
        if (grounded && p_keyboard_event->getKeyboardAction() == df::KEY_PRESSED) {
            y = -0.6*2;
        }
        break;

    case df::Keyboard::Q:  // Quit
        if (p_keyboard_event->getKeyboardAction() == df::KEY_PRESSED)
            WM.markForDelete(this);
        break;

    default:
        break;
    };
}


// Move up or down.
void Hero::move(int dy) {

    // See if time to move.
    if (move_countdown > 0)
        return;
    move_countdown = move_slowdown;

    // If stays on window, allow move.
    df::Vector new_pos(getPosition().getX(), getPosition().getY() + dy);
    if ((new_pos.getY() > 3) &&
        (new_pos.getY() < WM.getBoundary().getVertical() - 1))
        WM.moveObject(this, new_pos);



    // A d j u s t v i ew .
    df::Box new_view = WM.getView();
    df::Vector corner = new_view.getCorner();
    corner.setY(corner.getY() + dy);
    new_view.setCorner(corner);
    WM.setView(new_view);
}
void Hero::fire(df::Vector target) {
    LM.writeLog("FIRE FUNCTION CALLED");

    // See if time to fire.
    if (fire_countdown > 0) {
        LM.writeLog("CANNOT FIRE YET: Countdown = %d", fire_countdown);
        return;
    }
    fire_countdown = fire_slowdown;

    // Fire Bullet towards target.
    Bullet* p = new Bullet(getPosition());
    p->setVelocity(df::Vector(p->getVelocity().getX(),
        (target.getY() - getPosition().getY()) /
        (target.getX() - getPosition().getX())));

    LM.writeLog("BULLET CREATED AT (%f, %f)", getPosition().getX(), getPosition().getY());

    // Play "fire" sound.
    df::Sound* p_sound = RM.getSound("fire");
    if (p_sound) {
        LM.writeLog("PLAYING FIRE SOUND");
        p_sound->play();
    }
    else {
        LM.writeLog("FIRE SOUND NOT FOUND");
    }
}


// Decrease rate restriction counters.
void Hero::step() {

    // Move countdown.
    move_countdown--;
    if (move_countdown < 0)
        move_countdown = 0;

    // Fire countdown.
    fire_countdown--;
    if (fire_countdown < 0)
        fire_countdown = 0;
    df::Vector v = df::Vector(this->getPosition().getX(), this->getPosition().getY() + 1.5);
    df::ObjectList objL = WM.getCollisions(this,v);
    for (int i = 0; i < objL.getCount(); i++) {
        std::cout << objL[i]<<std::endl;
    }
    //jumping
    if ((!objL.isEmpty())&&(objL[0]->getType()=="Ground")) {
        grounded = true;
    }
    else {
        grounded = false;
    }


    if (grounded) {
        this->setVelocity(df::Vector(x, y));
    }
    else {
        y = 0;
        this->setVelocity(df::Vector(x, this->getVelocity().getY() + 0.02*2));//gravity

    }
    // A d j u s t v i ew .
    df::Box new_view = WM.getView();
    df::Vector corner = new_view.getCorner();
    corner.setY(corner.getY());
    new_view.setCorner(corner);
    WM.setView(new_view);

    
}

// Send "nuke" event to all objects.
void Hero::nuke() {

    // Check if nukes left.
    if (!nuke_count)
        return;
    nuke_count--;

    // Create "nuke" event and send to interested Objects.
    EventNuke nuke;
    WM.onEvent(&nuke);

    // Send "view" event do decrease number of nukes to interested ViewObjects.
    df::EventView ev("Nukes", -1, true);
    WM.onEvent(&ev);

    // Play "nuke" sound.
    df::Sound* p_sound = RM.getSound("nuke");
    p_sound->play();
}
