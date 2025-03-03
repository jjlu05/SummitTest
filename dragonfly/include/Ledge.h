//
// Ledge.h
//

#include "Object.h"
#include "EventCollision.h"

class Ledge : public df::Object {

private:


	void hit(const df::EventCollision* p_collision_event);

public:
	Ledge();
	int eventHandler(const df::Event* p_e);
};
