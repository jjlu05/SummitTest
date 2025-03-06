#include "Object.h"
#include "EventCollision.h"
#include "Hero.h"


class Checkpoint : public df::Object {
private:
	void hit(const df::EventCollision* p_collision_event);
	void nextLevel();
	void win();
	int level;
	Hero* p_hero;


public:
	Checkpoint(Hero* a_hero);
	int eventHandler(const df::Event* p_e) override;
};
