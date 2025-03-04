//
// Wall.h
//

#include "Object.h"
#include "EventCollision.h"

class Wall : public df::Object {

private:
	int id;  


	void hit(const df::EventCollision* p_collision_event);

public:
	Wall();
	Wall(int num);
	int eventHandler(const df::Event* p_e);
};
