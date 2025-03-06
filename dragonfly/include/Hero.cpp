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
#include "Bar.h"
#include "EventView.h"

bool allowLMove = true;
bool allowRMove = true;
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
    std::cout << "Should be deleted";
   /* df::ObjectList allObjs = WM.getAllObjects();
    Object* temp = nullptr;
    for (int i = 0; i < allObjs.getCount(); i++) {
        if (allObjs[i]->getType() == "Bar") {
            temp = allObjs[i];
            temp->setPosition(df::Vector(this->getPosition().getX(), this->getPosition().getY() + 2));
        }

    }
    WM.markForDelete(temp);*/
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
    df::EventView ev1("LIVES:", -1, true);


    if (p_e->getType() == df::OUT_EVENT) {
        lives--;
        if (lives != 0) {
            setPosition(df::Vector(70, 60));
            this->setVelocity(df::Vector(0, 0));
            WM.onEvent(&ev1);
            return 1;
        }
        else {
            WM.onEvent(&ev1);

            WM.markForDelete(this);
        }
       
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
            df::Vector vSide = df::Vector(this->getPosition().getX() - 1, this->getPosition().getY());
            df::ObjectList objS = WM.getCollisions(this, vSide);
            df::Vector vSide2 = df::Vector(this->getPosition().getX() + 1, this->getPosition().getY());
            df::ObjectList objS2 = WM.getCollisions(this, vSide2);
            if ((!objS.isEmpty()) || (!objS2.isEmpty())) {
                std::cout << "Side collision";
                x = 0;  
             }
        }
        return 1;
    }
    return 0;
}
int Hero::returnLives() {
    return lives;
}
// Mouse event handler.
void Hero::mouse(const df::EventMouse* p_mouse_event) {
    // Currently unused.
}


// Keyboard event handler.
void Hero::kbd(const df::EventKeyboard* p_keyboard_event) {
    switch (p_keyboard_event->getKey()) {
    case df::Keyboard::A:
        if (p_keyboard_event->getKeyboardAction() == df::KEY_PRESSED) {
            holdingA = true;
            if (xCountdown == 0) {
                if (grounded) {
                    if (allowLMove) {
                        desiredX = -0.3 * 2 * 1.5;
                        x = desiredX;
                    }
                }
                else {
                    desiredX = -0.3 * 2 * 1.5;
                    x = desiredX;
                }
                
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
                if (grounded) {
                    if (allowRMove) {
                        desiredX = 0.3 * 2 * 1.5;
                        x = desiredX;
                    }
                }
                else {
                    desiredX = 0.3 * 2 * 1.5;
                    x = desiredX;
                }
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
        if (p_keyboard_event->getKeyboardAction() == df::KEY_PRESSED) {
            if (allowJump) {
                // Only start a jump if the hero is grounded.
                if (grounded) {
                    ij = true;
                    animationSwitch = 30;
                    jumping = true;
                    allowJump = false;
                    allowJumpCount = 40;
                    
                }
            }
           
        }
        else if (p_keyboard_event->getKeyboardAction() == df::KEY_RELEASED) {
            // Only complete the jump if it was initiated (jumping is true).
            if (jumping && grounded) {
                jumping = false;
                ij = false;
                y = -0.6 * 2 - jumpIncrementor / 100;
                jumpIncrementor = 0;
            }
            // If the space was pressed in air, do nothing on release.
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







// Step method.
void Hero::step() {

    df::Vector vGLeft(getPosition().getX() - 5.0, getPosition().getY() + 4.5);
    df::ObjectList colGLeft = WM.getCollisions(this, vGLeft);
    if (grounded&&jumping) {
        if (colGLeft.isEmpty()) {
            std::cout << "Nothing ground left";
            allowLMove = false;
            if (desiredX < 0) {
                desiredX = 0;
            };

        }
        else {
            allowLMove = true;

        }
    }

   
    df::Vector vGRight(getPosition().getX() + 5.0, getPosition().getY() + 4.5);
    df::ObjectList colGRight = WM.getCollisions(this, vGRight);
    if (grounded && jumping) {
        if (colGRight.isEmpty()) {
            std::cout << "Nothing ground right";
            allowRMove = false;
            if (desiredX > 0) {
                desiredX = 0;
            };

        }
        else {
            allowRMove = true;

        }
    }







    allowScoreDec--;
    if (allowScoreDec == 0) {
        df::EventView ev2("SCORE:", -1, true);
        WM.onEvent(&ev2);
        allowScoreDec=100;
    }

    allowJumpCount--;
    if (allowJumpCount == 0) {
        allowJump = true;
        allowJumpCount = 40;
    }
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
        float MAX_JUMP = 55.0;
        jumpIncrementor++;
        if (jumpIncrementor > MAX_JUMP) {
            jumpIncrementor = 0;
        }
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
    df::Vector v(getPosition().getX(), getPosition().getY() + getVelocity().getY()+1);
    df::ObjectList objL = WM.getCollisions(this, v);
    // Check collisions above.
    df::Vector vAbove(getPosition().getX(), getPosition().getY() - 1);
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
        setVelocity(df::Vector(x, 0));

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
    df::ObjectList allObjs = WM.getAllObjects();
    for (int i = 0; i < allObjs.getCount(); i++) {
        if (allObjs[i]->getType()=="Bar") {
            Object* temp = allObjs[i];
            temp->setPosition(df::Vector(this->getPosition().getX(), this->getPosition().getY() + 2));
        }
    
    }

}

 



bool Hero::allowJumpGrounded() {
    return allowJump && grounded;
}

bool Hero::jumpingGrounded() {
    return jumping && grounded;
}