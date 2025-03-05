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
#include "EventOut.h"

// Global variables (ideally these should be members, but kept here for simplicity).
bool jumping = false;
bool grounded = false;
bool gAbove = false;
float x = 0;   // Actual horizontal velocity applied.
float y = 0;   // Vertical velocity.
float jumpIncrementor = 0;
int xCountdown = 0;
bool ij = false;
float animationSwitch = 0;
Hero::Hero() {
    // Link to "ship" sprite.
    setSprite("hero");
    std::cout<<this->getAnimation().getSlowdownCount();
    // Register interest for events.
#ifdef DF_REGISTER_INTEREST
    registerInterest(df::KEYBOARD_EVENT);
    registerInterest(df::MSE_EVENT);
    registerInterest(df::STEP_EVENT);
#endif

    // Set object type.
    setType("Hero");
    // WM.setViewFollowing(this);  

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

    // Initialize desiredX (declared in Hero.h) and our current x.
    desiredX = 0;
    x = 0;
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

    if (p_e->getType() == df::OUT_EVENT) {
        setPosition(df::Vector(120, 48));
        this->setVelocity(df::Vector(0, 0));
        return 1;
    }
    if (p_e->getType() == df::KEYBOARD_EVENT) {
        const df::EventKeyboard* p_keyboard_event = dynamic_cast<const df::EventKeyboard*>(p_e);
        kbd(p_keyboard_event);
        return 1;
    }
    if (p_e->getType() == df::MSE_EVENT) {
        LM.writeLog("MOUSE EVENT HAPPENED");
        const df::EventMouse* p_mouse_event = dynamic_cast<const df::EventMouse*>(p_e);
        mouse(p_mouse_event);
        return 1;
    }
    if (p_e->getType() == df::STEP_EVENT) {
        step();
        return 1;
    }
    if (p_e->getType() == df::COLLISION_EVENT) {
        const df::EventCollision* p_collision_event = dynamic_cast<const df::EventCollision*>(p_e);
        // Handle collisions with Bat.
        if (((p_collision_event->getObject1()->getType()) == "Bat") ||
            ((p_collision_event->getObject2()->getType()) == "Bat"))
        {
            xCountdown = 10;
            x = -getVelocity().getX();
            y = -1;
        }
        // Handle collisions with Wall.
        if (((p_collision_event->getObject1()->getType()) == "Wall") ||
            ((p_collision_event->getObject2()->getType()) == "Wall"))
        {
            x = 0;
        }
        // Handle collisions with Ground.
        if (((p_collision_event->getObject1()->getType()) == "Ground") ||
            ((p_collision_event->getObject2()->getType()) == "Ground"))
        {
            std::cout << "touching";
            // Check for side collisions by looking slightly left and right.
            df::Vector vSide = df::Vector(this->getPosition().getX() - 1, this->getPosition().getY());
            df::ObjectList objS = WM.getCollisions(this, vSide);
            df::Vector vSide2 = df::Vector(this->getPosition().getX() + 1, this->getPosition().getY());
            df::ObjectList objS2 = WM.getCollisions(this, vSide2);
            if ((!objS.isEmpty()) || (!objS2.isEmpty())) {
                std::cout << "Side collision";
                x = 0;  // Cancel actual horizontal velocity.
                // Note: We do NOT change desiredX here so that it remembers what the player wanted.
            }
        }
        return 1;
    }
    return 0;
}

// Mouse event handler.
void Hero::mouse(const df::EventMouse* p_mouse_event) {
    // Currently unused.
}

// Track key states.
bool holdingA = false;
bool holdingD = false;

// Keyboard event handler.
void Hero::kbd(const df::EventKeyboard* p_keyboard_event) {
    switch (p_keyboard_event->getKey()) {
    case df::Keyboard::A:
        if (p_keyboard_event->getKeyboardAction() == df::KEY_PRESSED) {
            holdingA = true;
            if (xCountdown == 0) {
                desiredX = -0.3 * 2 * 1.5;
                x = desiredX;
            }
        }
        if (p_keyboard_event->getKeyboardAction() == df::KEY_RELEASED) {
            holdingA = false;
            if (xCountdown == 0) {
                if (!holdingD) {
                    desiredX = 0;
                    x = 0;
                }
            }
        }
        break;
    case df::Keyboard::D:
        if (p_keyboard_event->getKeyboardAction() == df::KEY_PRESSED) {
            holdingD = true;
            if (xCountdown == 0) {
                desiredX = 0.3 * 2 * 1.5;
                x = desiredX;
            }
        }
        if (p_keyboard_event->getKeyboardAction() == df::KEY_RELEASED) {
          

            holdingD = false;
            if (xCountdown == 0) {
                if (!holdingA) {
                    desiredX = 0;
                    x = 0;
                }
            }
           
        }
        break;
    case df::Keyboard::SPACE:
        if (grounded && p_keyboard_event->getKeyboardAction() == df::KEY_PRESSED) {
            ij = true;
            animationSwitch = 30;
            /*y = -0.6 * 2;*/
            //set animation to 30, set frame to 1
            //every step event, decrease animation
        }   jumping = true;
        if (grounded && p_keyboard_event->getKeyboardAction() == df::KEY_RELEASED) {
            jumping = false;
            ij = false;
            y = -0.6 * 2-jumpIncrementor/100;
            jumpIncrementor = 0;
        }
        break;
    case df::Keyboard::Q:  // Quit
        if (p_keyboard_event->getKeyboardAction() == df::KEY_PRESSED)
            WM.markForDelete(this);
        break;
    default:
        break;
    }
}

// Move method.
void Hero::move(int dy) {
    if (move_countdown > 0)
        return;
    move_countdown = move_slowdown;
    df::Vector new_pos(getPosition().getX(), getPosition().getY() + dy);
    if ((new_pos.getY() > 3) &&
        (new_pos.getY() < WM.getBoundary().getVertical() - 1))
        WM.moveObject(this, new_pos);
    df::Box new_view = WM.getView();
    df::Vector corner = new_view.getCorner();
    corner.setY(corner.getY() + dy);
    new_view.setCorner(corner);
    WM.setView(new_view);
}

// Fire method.
void Hero::fire(df::Vector target) {
    LM.writeLog("FIRE FUNCTION CALLED");
    if (fire_countdown > 0) {
        LM.writeLog("CANNOT FIRE YET: Countdown = %d", fire_countdown);
        return;
    }
    fire_countdown = fire_slowdown;
    Bullet* p = new Bullet(getPosition());
    p->setVelocity(df::Vector(p->getVelocity().getX(),
        (target.getY() - getPosition().getY()) /
        (target.getX() - getPosition().getX())));
    LM.writeLog("BULLET CREATED AT (%f, %f)", getPosition().getX(), getPosition().getY());
    df::Sound* p_sound = RM.getSound("fire");
    if (p_sound) {
        LM.writeLog("PLAYING FIRE SOUND");
        p_sound->play();
    }
    else {
        LM.writeLog("FIRE SOUND NOT FOUND");
    }
}

// Step method.
void Hero::step() {
    if (this->getVelocity().getY() >0) {
        setSprite("hero-fall");
    }
    else if (jumping) {
        if (animationSwitch > 15) {
            std::cout << "Number1";
            setSprite("hero-crouch");
        }
        else if (animationSwitch > 0) {
            setSprite("hero-squat");
        }
    }
   
    else {
        setSprite("hero");
    }
    animationSwitch--;
    if (ij) {
        jumpIncrementor++;
    }
    // Decrease countdowns.
    if (xCountdown > 0) {
        xCountdown--;
    }
    move_countdown--;
    if (move_countdown < 0)
        move_countdown = 0;
    fire_countdown--;
    if (fire_countdown < 0)
        fire_countdown = 0;

    // Check collisions below.
    df::Vector v(getPosition().getX(), getPosition().getY() + 1.33);
    df::ObjectList objL = WM.getCollisions(this, v);
    // Check collisions above.
    df::Vector vAbove(getPosition().getX(), getPosition().getY() - 1.33);
    df::ObjectList objAbove = WM.getCollisions(this, vAbove);

    // Update grounded state.
    if ((!objL.isEmpty()) && (objL[0]->getType() == "Ground")) {
        grounded = true;
    }
    else if ((!objAbove.isEmpty()) && (objAbove[0]->getType() == "Ground")) {
        gAbove = true;
        grounded = false;
    }
    else {
        gAbove = false;
        grounded = false;
    }

    // Restore horizontal velocity if no side collision.
    {
        df::Vector vLeft(getPosition().getX() - 1, getPosition().getY());
        df::ObjectList leftCollisions = WM.getCollisions(this, vLeft);
        df::Vector vRight(getPosition().getX() + 1, getPosition().getY());
        df::ObjectList rightCollisions = WM.getCollisions(this, vRight);
        bool sideCollision = (!leftCollisions.isEmpty() || !rightCollisions.isEmpty());
        if (!sideCollision) {
            x = desiredX;
        }
    }

    // Apply velocity based on collision state.
    if (grounded) {
        this->setVelocity(df::Vector(x, y));
    }
    else if (gAbove) {
        float currentY = this->getVelocity().getY();
        if (currentY < 0) {
            this->setVelocity(df::Vector(x, -currentY));
        }
        else {
            this->setVelocity(df::Vector(x, 1.0));
        }
    }
    else {
        y = 0;
        const float MAX_FALL_SPEED = 2.0f;
        float newYVelocity = this->getVelocity().getY() + (0.02 * 3);
        if (newYVelocity > MAX_FALL_SPEED) {
            newYVelocity = MAX_FALL_SPEED;
        }
        this->setVelocity(df::Vector(x, newYVelocity));
    }
}

// Send "nuke" event to all objects.
void Hero::nuke() {
    if (!nuke_count)
        return;
    nuke_count--;
    EventNuke nuke;
    WM.onEvent(&nuke);
    df::EventView ev("Nukes", -1, true);
    WM.onEvent(&ev);
    df::Sound* p_sound = RM.getSound("nuke");
    p_sound->play();
}
