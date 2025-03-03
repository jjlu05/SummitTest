//
// Wall.h
//

#include "Object.h"
#include "EventCollision.h"

class Wall : public df::Object {

private:


	void hit(const df::EventCollision* p_collision_event);

public:
	Wall();
	int eventHandler(const df::Event* p_e);
};
