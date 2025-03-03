//
// Ground.h
//

#include "Object.h"
#include "EventCollision.h"

class Ground : public df::Object {

private:

	
	void hit(const df::EventCollision* p_collision_event);

public:
	Ground();
	int eventHandler(const df::Event* p_e);
};
