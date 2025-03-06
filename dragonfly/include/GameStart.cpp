//
// GameStart.cpp
//

// Engine includes.
#include "Color.h"
#include "EventKeyboard.h"
#include "GameManager.h"
#include "LogManager.h"
#include "ResourceManager.h"
#include "WorldManager.h"
#include "DisplayManager.h"
// Game includes.
#include "GameStart.h"
#include "Hero.h"
#include "Music.h"
#include "Points.h"
#include "Saucer.h"
#include <iostream>
#include "Ground.h"
#include "Ledge.h"
#include "Bat.h"
#include "Wall.h"
#include "Skeleton.h"
#include "Mole.h"
#include "ViewObject.h"
#include "WorldManager.h"
#include "utility.h"
#include <string>
#include "EventView.h"
#include "Bar.h"
#include "Checkpoint.h"

int position = 4;
bool started1 = false;
GameStart::GameStart() {
    std::cout << "GameStarted";
    setType("GameStart");

    // Link to "message" sprite.
    setSprite("gamestart");

    // Put in center of screen.
    //setLocation(df::CENTER_CENTER);
    setPosition(df::Vector(40, 10));
    // Register for "keyboard" event.
#ifdef DF_REGISTER_INTEREST
    registerInterest(df::KEYBOARD_EVENT);
#endif

    // Play start music.
    p_music = RM.getMusic("menu");
    playMusic();
    wind = RM.getMusic("wind");
    wind->play();
    
}

// Play start music.
void GameStart::playMusic() {
    p_music->play();
}

// Handle event.
// Return 0 if ignored, else 1.
int GameStart::eventHandler(const df::Event* p_e) {

    if (p_e->getType() == df::KEYBOARD_EVENT) {
        df::EventKeyboard* p_keyboard_event = (df::EventKeyboard*)p_e;
        if (p_keyboard_event->getKeyboardAction() == df::KEY_PRESSED)
            switch (p_keyboard_event->getKey()) {
            case df::Keyboard::P: 			// play
                std::cout << "PRESSED";
                started1 = true;
                start();

                break;
            case df::Keyboard::Q:			// quit
                GM.setGameOver();
                started1 = false;
                break;
            default:
                break;
            }
        return 1;
    }

    // If get here, have ignored this event.
    return 0;
}
bool GameStart::started() {
    return started1;

}
void GameStart::start() {
    df::ViewObject* border1 = new df::ViewObject();
    border1->setBorder(false);
    border1->setViewString("----------");
    border1->setDrawValue(false);
    border1->setPosition(df::Vector(10, 2));

    df::ViewObject* vObj = new df::ViewObject();
    vObj->setViewString("LIVES:");
    vObj->setValue(3);
    vObj->setPosition(df::Vector(10, 1));
    vObj->setBorder(false);



    df::ViewObject* score = new df::ViewObject();
    score->setViewString("SCORE:");
    score->setValue(100);
    score->setPosition(df::Vector(37, 1));
    score->setBorder(false);
    df::ViewObject* border2 = new df::ViewObject();
    border2->setBorder(false);
    border2->setViewString("----------");
    border2->setDrawValue(false);
    border2->setPosition(df::Vector(37, 2));



    //120
    // 48
  // Create hero.






    Object* deaths = new Object();
    Object* background = new Object();
    background->setSolidness(df::SPECTRAL);
    background->setPosition(df::Vector(20, 50));
    background->setSprite("background");
    Object* background2 = new Object();
    background2->setSolidness(df::SPECTRAL);
    background2->setPosition(df::Vector(85, 70));
    background2->setSprite("background");

    /*Bar* bar = new Bar();
    bar->setSolidness(df::SPECTRAL);
    bar->setPosition(df::Vector(70, 56));*/

    Bar* bar = new Bar();
    bar->setSolidness(df::SPECTRAL);
    bar->setPosition(df::Vector(70, 56));
    bar->setType("Bar");
    bar->setSprite("bar");
    Hero* hero = new Hero();
    int center_x = DM.getHorizontal() / 2;
    int center_y = DM.getVertical() / 2;
    hero->setPosition(df::Vector(70, 60));
 /*   Skeleton* skel = new Skeleton(hero);
    skel->setPosition(df::Vector(80, 30));
    Skeleton* skel2 = new Skeleton(hero);
    skel2->setPosition(df::Vector(150, 57));*/

    Checkpoint* chkpt = new Checkpoint(hero);
    chkpt->setSprite("checkpoint");
    chkpt->setPosition(df::Vector(10, 10));

    Wall* wall = new Wall(1);
    wall->setPosition(df::Vector(0, 40));
    Wall* wall2 = new Wall(2);
    wall2->setPosition(df::Vector(108, 44));

   /* Bat* bat = new Bat();
    bat->setPosition(df::Vector(80, 65));*/
    Ground* ground = new Ground();
    ground->setPosition(df::Vector(70, 80));
    // Setup heads-up display.
    //Points *tPoints = new Points;		                     // Points display.
    //df::ViewObject *p_vo = new df::ViewObject; // Count of nukes.
    //p_vo->setLocation(df::TOP_LEFT);
    //p_vo->setViewString("Nukes");
    //p_vo->setValue(1);
    //p_vo->setColor(df::YELLOW);
    // Pause start music.

    //Mole* mole = new Mole;
    //mole->setPosition(df::Vector(80, 40));
    p_music->pause();

    // When game starts, destroy this object.
    WM.markForDelete(this);


    Ledge* ledge = new Ledge();
    ledge->setPosition(df::Vector(18 * position, 14 * position));
    Ledge* ledge1 = new Ledge();
    ledge1->setPosition(df::Vector(30, 40));

    Mole* mole = new Mole();
    mole->setPosition(df::Vector(60, 40));


}

// Override default draw so as not to display "value".
int GameStart::draw() {
    df::Object::draw();
    return 0;
}
