
#include "Checkpoint.h"
#include "Ground.h"
#include "Ledge.h"
#include "Mole.h"
#include "Skeleton.h"
#include "Bat.h"

#include "WorldManager.h"
#include "ObjectList.h"
#include "LogManager.h"

Checkpoint::Checkpoint(Hero* a_hero) {
	level = 1;
	setType("Checkpoint");
	setSprite("checkpoint");
	p_hero = a_hero;
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
		if (level != 4) {
			setPosition(df::Vector(getPosition().getX() + 10, getPosition().getY()));
			nextLevel();
		}
		else {
			win();
		}
	}
}

void Checkpoint::nextLevel() {

	LM.writeLog("nextLevel %i", level);
	//Increment level
	level++;
	LM.writeLog("nextLevel %i", level);
	df::ObjectList objs = WM.getAllObjects();

	//Delete all objects from level to set up new level
	for (int i = 0; i < objs.getCount(); i++) {
		df::Object* p_cur_obj = objs[i];

		if (p_cur_obj->getType() == "Hero") {
			p_cur_obj->setPosition(df::Vector(70, 60));
		}

		if (p_cur_obj->getType() != "Checkpoint" && p_cur_obj->getType() != "Wall" && p_cur_obj->getType() != "Hero" && p_cur_obj->getType() != "ViewObject" &&
			p_cur_obj->getType() != "Bar")
			WM.removeObject(p_cur_obj);

	}

	if (level == 4) {
		Ground* ground = new Ground();
		ground->setPosition(df::Vector(70, 80));

		Ledge* ledge1 = new Ledge;
		ledge1->setPosition(df::Vector(10, 63));

		Ledge* ledge2 = new Ledge;
		ledge2->setPosition(df::Vector(70, 40));

		Ledge* ledge3 = new Ledge;
		ledge3->setPosition(df::Vector(50, 50));

		Mole* mole1 = new Mole;
		mole1->setPosition(df::Vector(50, 40));

		Skeleton* skel1 = new Skeleton(p_hero);
		skel1->setPosition(df::Vector(80, 10));

		Ledge* ledge4 = new Ledge;
		ledge4->setPosition(df::Vector(20, 25));

		Bat* bat1 = new Bat;
		bat1->setPosition(df::Vector(20, 43));

		Bat* bat2 = new Bat;
		bat2->setPosition(df::Vector(50, 66));
	}
	else if (level == 3) {
		Ground* ground = new Ground();
		ground->setPosition(df::Vector(70, 80));

		for (int i = 0; i < 5; i++) {
			Bat* bat = new Bat;
			bat->setPosition(df::Vector(5 + (rand() % 91), 60 - (i * 10)));

			df::Vector new_spd = df::Vector(((rand() % 3) * 0.5) + 0.3, 0);
			bat->setVelocity(new_spd);
		}

		Ledge* ledge1 = new Ledge;
		ledge1->setPosition(df::Vector(100, 45));

		Ledge* ledge2 = new Ledge;
		ledge2->setPosition(df::Vector(42, 35));

		Skeleton* skel = new Skeleton(p_hero);
		skel->setPosition(df::Vector(40, 45));
	}
	else if (level == 2) {
		Ground* ground = new Ground();
		ground->setPosition(df::Vector(70, 80));

		Ledge* ledge1 = new Ledge;
		ledge1->setPosition(df::Vector(10, 55));

		Ledge* ledge2 = new Ledge;
		ledge2->setPosition(df::Vector(50, 55));

		Ledge* ledge3 = new Ledge;
		ledge3->setPosition(df::Vector(90, 55));

		Mole* mole1 = new Mole;
		mole1->setPosition(df::Vector(15, 45));

		Mole* mole2 = new Mole;
		mole2->setPosition(df::Vector(50, 45));

		Mole* mole3 = new Mole;
		mole3->setPosition(df::Vector(100, 45));

		Ledge* ledge4 = new Ledge;
		ledge4->setPosition(df::Vector(25, 40));

		Ledge* ledge5 = new Ledge;
		ledge5->setPosition(df::Vector(75, 40));

		Mole* mole4 = new Mole;
		mole4->setPosition(df::Vector(25, 35));

		Mole* mole5 = new Mole;
		mole5->setPosition(df::Vector(75, 35));

		Ledge* ledge6 = new Ledge;
		ledge6->setPosition(df::Vector(50, 25));

		Skeleton* skel = new Skeleton(p_hero);
		skel->setPosition(df::Vector(85, 10));
	}
}

void Checkpoint::win() {

	p_hero->setPosition(df::Vector(70, 60));

	df::ObjectList objs = WM.getAllObjects();

	//Delete all objects from level to set up winning screen
	for (int i = 0; i < objs.getCount(); i++) {
		df::Object* p_cur_obj = objs[i];

		if ((p_cur_obj->getType() == "Ground") || (p_cur_obj->getType() == "Mole") || (p_cur_obj->getType() == "Skeleton") || (p_cur_obj->getType() == "Bat"))
			WM.markForDelete(p_cur_obj);

	}

	Ground* ground = new Ground;
	ground->setPosition(df::Vector(70, 80));

	//create win view object
}


