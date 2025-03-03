#include "Object.h"
#include "EventCollision.h"

class Bat : public df::Object {
private:
	void hit(const df::EventCollision* p_collision_event);
public:
	Bat();
	int eventHandler(const df::Event* p_e) override;
};
