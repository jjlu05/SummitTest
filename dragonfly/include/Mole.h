#include "Object.h"
#include "EventCollision.h"

class Mole : public df::Object {
private:
	void hit(const df::EventCollision* p_collision_event);
	void step();
	bool grounded;
	bool ledge_found;

public:
	Mole();
	int eventHandler(const df::Event* p_e) override;
	bool getGrounded() const;
};
