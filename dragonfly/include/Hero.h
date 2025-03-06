//
// Hero.h
//
#ifndef HERO_H
#define HERO_H
#include "EventKeyboard.h"
#include "EventMouse.h"
#include "Object.h"
#include "Reticle.h"

class Hero : public df::Object {

 private:

	 float allowScoreDec = 100;

	 int allowJumpCount = 0;
	 bool allowJump = true;
	 int lives = 3;
	 // Track key states.
	 bool holdingA = false;
	 bool holdingD = false;

	 float desiredX;
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
	 bool inAir = false;
  Reticle *p_reticle;
  int fire_slowdown;
  int fire_countdown;
  int move_slowdown;
  int move_countdown;
  int nuke_count;
  void mouse(const df::EventMouse *p_mouse_event);
  void kbd(const df::EventKeyboard *p_keyboard_event);
  void move(int dy);
  void fire(df::Vector target);
  void step();
  void nuke();

 public:
  Hero();
  ~Hero();
  int eventHandler(const df::Event *p_e);
  int returnLives();
  bool allowJumpGrounded();
  bool jumpingGrounded();

};
#endif