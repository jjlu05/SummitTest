#include "Object.h"
#include "EventCollision.h"


class Checkpoint : public df::Object {
private:
	void hit(const df::EventCollision* p_collision_event);
	void nextLevel();
	void win();
	int level;

public:
	Checkpoint();
	int eventHandler(const df::Event* p_e) override;
};

