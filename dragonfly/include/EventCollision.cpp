// EventCollision.cpp
#include "EventCollision.h"
#include "Event.h"   // Ensure the base Event class is included
#include "Object.h"
#include "Vector.h"
namespace df {

    EventCollision::EventCollision() {
        setType(COLLISION_EVENT);

        m_pos = Vector(0, 0);
        m_p_obj1 = nullptr;
        m_p_obj2 = nullptr;
    };


    EventCollision::EventCollision(Object* p_o1, Object* p_o2, Vector p) {
        setType(COLLISION_EVENT);

        m_pos = p;
        m_p_obj1 = p_o1;
        m_p_obj2 = p_o2;
    };

    // Set the object that caused the collision.
    void EventCollision::setObject1(Object* p_new_o1) {
        m_p_obj1 = p_new_o1;
    }

    // Return the object that caused the collision.
    Object* EventCollision::getObject1() const {
        return m_p_obj1;
    }

    // Set the object that was collided with.
    void EventCollision::setObject2(Object* p_new_o2) {
        m_p_obj2 = p_new_o2;
    }

    // Return the object that was collided with.
    Object* EventCollision::getObject2() const {
        return m_p_obj2;
    }

    // Set the position where the collision occurred.
    void EventCollision::setPosition(Vector new_pos) {
        m_pos = new_pos;
    }

    // Return the collision position.
    Vector EventCollision::getPosition() const {
        return m_pos;
    }


}