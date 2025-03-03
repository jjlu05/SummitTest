#include "Object.h"
#include "EventCollision.h"
#include "Hero.h"
class Skeleton : public df::Object {
private:
	void hit(const df::EventCollision* p_collision_event);
	void attack();
	void step();
	df::Box attack_range;
	Hero *p_hero;
	int attack_slowdown;
	int attack_cooldown;

public:
	Skeleton(Hero *a_hero);
	int eventHandler(const df::Event* p_e) override;
};
