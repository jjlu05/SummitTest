
#include "Object.h"
#include "EventCollision.h"

class Arrow : public df::Object {
private:
	void hit(const df::EventCollision* p_collision_event);
	void out();
	void step();
	int death_timer;
public:
	Arrow(df::Vector skel_pos);
	~Arrow();
	int eventHandler(const df::Event* p_e) override;
};
