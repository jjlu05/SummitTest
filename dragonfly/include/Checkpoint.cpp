
#include "Checkpoint.h"
#include "WorldManager.h"
#include "ObjectList.h"

Checkpoint::Checkpoint() {
	level = 1;
	setType("Checkpoint");
	setSprite("checkpoint");
}

int Checkpoint::eventHandler(const df::Event* p_e) {
	if (p_e->getType() == df::COLLISION_EVENT) {
		const df::EventCollision* p_collision_event = dynamic_cast <df::EventCollision const*> (p_e);
		hit(p_collision_event);
		return 1;
	}
}

void Checkpoint::hit(const df::EventCollision* p_collision_event) {
	if (((p_collision_event->getObject1()->getType()) == "Hero") ||
		((p_collision_event->getObject2()->getType()) == "Hero")) {
		if (level > 3) {
			nextLevel();
		}
		else {
			win();
		}
	}
}

void Checkpoint::nextLevel() {
	//Increment level
	level++;

	df::ObjectList objs = WM.getAllObjects();

	//Delete all objects from level to set up new level
	for (int i = 0; i < objs.getCount(); i++) {
		df::Object* p_cur_obj = objs[i];
		
		if(p_cur_obj->getType()!="Checkpoint")
			WM.removeObject(p_cur_obj);
		
	}

	if (level == 2) {
		//level configiration for level 2
	}
	else if (level == 3) {
		//level configuration for level 3
	}
}

void Checkpoint::win() {

	df::ObjectList objs = WM.getAllObjects();

	//Delete all objects from level to set up winning screen
	for (int i = 0; i < objs.getCount(); i++) {
		df::Object* p_cur_obj = objs[i];
		
		if ((p_cur_obj->getType() != "Checkpoint")&&(p_cur_obj->getType()!="Wall"))
			WM.markForDelete(p_cur_obj);
		
	}

	//create win view object
}
