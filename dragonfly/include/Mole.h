#include "Object.h"
#include "EventCollision.h"

class Mole : public df::Object {
private:
	void hit(const df::EventCollision* p_collision_event);
	
public:
	Mole();
	int eventHandler(const df::Event* p_e) override;
};
