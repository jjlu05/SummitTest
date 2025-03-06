//
// Bar.h
//
#ifndef BAR_H
#define BAR_H
#include "EventKeyboard.h"
#include "EventMouse.h"
#include "Object.h"
#include "Reticle.h"

class Bar : public df::Object {

private:// Track key states.
	float allowScoreDec = 100;

	int allowJumpCount = 0;
	bool allowJump = true;
	bool holdingA = false;
	bool holdingD = false;
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
	float desiredX;

	Reticle* p_reticle;
	int fire_slowdown;
	int fire_countdown;
	int move_slowdown;
	int move_countdown;
	int nuke_count;
	void mouse(const df::EventMouse* p_mouse_event);
	void kbd(const df::EventKeyboard* p_keyboard_event);
	void move(int dy);
	void fire(df::Vector target);
	void step();
	void nuke();

public:
	Bar();
	~Bar();
	int eventHandler(const df::Event* p_e);
	void reset();
};
#endif