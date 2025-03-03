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
  p_music = RM.getMusic("start music");
  playMusic();
}

// Play start music.
void GameStart::playMusic() {
  p_music->play();
}

// Handle event.
// Return 0 if ignored, else 1.
int GameStart::eventHandler(const df::Event *p_e) {

  if (p_e->getType() == df::KEYBOARD_EVENT) {
    df::EventKeyboard *p_keyboard_event = (df::EventKeyboard *) p_e;
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

  // Create hero.
  Hero* hero = new Hero();
  hero->setPosition(df::Vector(39, 15));

  //// Spawn some saucers to shoot.
  //for (int i=0; i<16; i++)
  //  new Saucer;
  Wall* wall = new Wall();
  wall->setPosition(df::Vector(0, 10));

  Bat* bat = new Bat();
  bat->setPosition(df::Vector(10, 10));
  Ground* ground = new Ground();
  ground->setPosition(df::Vector(39,20));
  // Setup heads-up display.
  Points *tPoints = new Points;		                     // Points display.
  df::ViewObject *p_vo = new df::ViewObject; // Count of nukes.
  p_vo->setLocation(df::TOP_LEFT);
  p_vo->setViewString("Nukes");
  p_vo->setValue(1);
  p_vo->setColor(df::YELLOW);
  // Pause start music.
  p_music->pause();

  // When game starts, destroy this object.
  WM.markForDelete(this);


  Ledge* ledge= new Ledge();
  ledge->setPosition(df::Vector(18, 14));



}

// Override default draw so as not to display "value".
int GameStart::draw() {
  df::Object::draw();
  return 0;
}
