#include "Object.h"
#include "WorldManager.h"
#include <string>
#include "ObjectList.h"
#include <iostream>  
#include "utility.h"

#include "EventCollision.h"
#include "DisplayManager.h"
#include "EventOut.h"
#include "ViewObject.h"
namespace df {

    //initializing both variables
    WorldManager::WorldManager() {
        setType("WorldManager");
        m_updates = ObjectList();
        m_deletions = ObjectList();
         boundary = Box(Vector(0, 0), 0, 0);
        view = Box(Vector(0, 0), DM.getHorizontal(), DM.getVertical()); // Centered, full screen view.
        //set the view and bound to DM.get


    }

    WorldManager& WorldManager::getInstance() {
        static WorldManager instance;
        return instance;
    }

    // Startup game world (initialize everything to empty).
    // Return 0.
    int WorldManager::startUp() {
        Manager::startUp();
        m_updates.clear();   
        m_deletions.clear();  
        return 0;
    }

    // Shutdown game world (delete all game world Objects).
    void WorldManager::shutDown() {
        ObjectList ol = m_updates;
        for (int i = 0; i < ol.getCount(); i++) {
            delete ol[i];
        }
        Manager::shutDown();
    }

    // Insert Object into world. Return 0 if ok, else -1.
    int WorldManager::insertObject(Object* p_o) {
        if (!p_o) return -1; // check null
        m_updates.insert(p_o);
        return 0; //success
    }

    // Remove Object from world. Return 0 if ok, else -1.
    int WorldManager::removeObject(Object* p_o) {
        if (!p_o) return -1; //null check
        m_updates.remove(p_o);
        return 0;
    }

    // Return list of all Objects in world.
    ObjectList WorldManager::getAllObjects() const {
        // Implement logic to return all objects.
        return m_updates;
    }

    // Return list of all Objects in world matching type.
    ObjectList WorldManager::objectsOfType(std::string type) const {
        ObjectList result;
        for (int i = 0; i < m_updates.getCount(); i++) {
            if (m_updates[i]->getType() == type) {
                result.insert(m_updates[i]);
            }
        }
        return result;
    }

    // Update world.
    // Delete Objects marked for deletion.
    void WorldManager::update() {
        for (int i = 0; i < m_deletions.getCount(); i++) {
            delete m_deletions[i];
        }

        m_deletions.clear();
        for (int i = 0; i < m_updates.getCount(); i++) {
            Vector new_pos = m_updates[i]->predictPosition();
            const float EPSILON = 0.001f;
            Vector old_pos = m_updates[i]->getPosition();
            if (fabs(new_pos.getX() - old_pos.getX()) > EPSILON ||
                fabs(new_pos.getY() - old_pos.getY()) > EPSILON) {
                moveObject(m_updates[i], new_pos);
            }

        }
    }

    // Indicate Object is to be deleted at end of current game loop.
    // Return 0 if ok, else -1.
    int WorldManager::markForDelete(Object* p_o) {
        for (int i = 0; i < m_deletions.getCount(); i++) {
            if (m_deletions[i] == p_o) {
                return 0;
            }
        }
        m_deletions.insert(p_o);
        return 0;  
    }

    
    void WorldManager::draw() {
        for (int j = 0; j < MAX_ALTITUDE; j++) {
            for (int i = 0; i < m_updates.getCount(); i++) {
                Box temp_box = getWorldBox(m_updates[i]);
                if (((m_updates[i]->getAltitude() == j) && (boxIntersectsBox(temp_box, view)))||dynamic_cast<ViewObject*>(m_updates[i])) {
                    m_updates[i]->draw();
                }
            }
        }
    }


//WATCHC OUT
    //MIGHT BE WRONG
    ObjectList WorldManager::getCollisions(const Object* p_o, Vector where) {
        ObjectList collision_list;

        // Get the world bounding box for p_o at the specified position 'where'
        Box b = getWorldBox(p_o, where);

        // Iterate over all objects in the update list
        for (int i = 0; i < m_updates.getCount(); i++) {
            Object* p_temp_o = m_updates[i];

            // Avoid checking collision with the object itself
            if (p_temp_o != p_o) {
                // Get the world bounding box for the current object
                Box b_temp = getWorldBox(p_temp_o);

                // If the bounding boxes intersect and the object is solid, add it to the collision list
                if (boxIntersectsBox(b, b_temp) && p_temp_o->isSolid()) {
                    collision_list.insert(p_temp_o);
                }
            }
        }
        return collision_list;
    }

    //int WorldManager::moveObject(Object* p_o, Vector where) {
    //    if (p_o->isSolid()) {
    //        ObjectList list = getCollisions(p_o, where);
    //        if (!list.isEmpty()) {
    //            bool do_move = true;
    //            for (int i = 0; i < list.getCount(); i++) {
    //                Object* p_temp_o = list[i];

    //                EventCollision c(p_o, p_temp_o, where);
    //                p_o->eventHandler(&c);
    //                p_temp_o->eventHandler(&c);
    //                
    //                if (p_o->getSolidness() == HARD && p_temp_o->getSolidness() == HARD) {
    //                    do_move = false;

    //                }
    //            }
    //            if (do_move == false) {
    //                return -1;
    //            }
    //        }
    //    
    //    }
    //    p_o->setPosition(where);

    //    if ((p_o->getPosition().getX() < 0 || p_o->getPosition().getX() > DM.getHorizontal()) ||
    //        (p_o->getPosition().getY() < 0 || p_o->getPosition().getY() > DM.getVertical())) {

    //        // generate EventOut if it hasn't been sent yet
    //        if (!p_o->getOutEventSent()) {
    //            EventOut ev;
    //            p_o->eventHandler(&ev);
    //            p_o->setOutEventSent(true);
    //        }
    //    }
    //    else {
    //      
    //        p_o->setOutEventSent(false);
    //    }
    //    return 0;
    //};

    int WorldManager::moveObject(Object* p_o, Vector where) {
        // Check for collisions if the object is solid.
        if (p_o->isSolid()) {
            ObjectList list = getCollisions(p_o, where);
            if (!list.isEmpty()) {
                bool do_move = true;
                for (int i = 0; i < list.getCount(); i++) {
                    Object* p_temp_o = list[i];

                    EventCollision c(p_o, p_temp_o, where);
                    p_o->eventHandler(&c);
                    p_temp_o->eventHandler(&c);

                    if (p_o->getSolidness() == HARD && p_temp_o->getSolidness() == HARD) {
                        do_move = false;
                    }
                }
                if (!do_move) {
                    return -1;
                }
            }
        }

        // Save the original world bounding box of the object.
        Box orig_box = getWorldBox(p_o);

        // Move the object.
        p_o->setPosition(where);
        if (p_view_following == p_o) {
            setViewPosition(p_o->getPosition());
        } 

        // Get the new world bounding box of the object after movement.
        Box new_box = getWorldBox(p_o);

        // If the object moved from inside to outside the world boundary, generate an EventOut.
        if (boxIntersectsBox(orig_box, boundary) && !boxIntersectsBox(new_box, boundary)) {
            if (!p_o->getOutEventSent()) {
                EventOut ev;
                p_o->eventHandler(&ev);
             }
        }
        else {
         }

        return 0;
    }



    // Set game world boundary.
    void WorldManager::setBoundary(Box new_boundary) {
        boundary = new_boundary;
    }

    // Get game world boundary.
    Box WorldManager::getBoundary() const {
        return boundary;
    }

    // Set player's view of game world.
    void WorldManager::setView(Box new_view) {
        view = new_view;
    }

    // Get player's view of game world.
    Box WorldManager::getView() const {
        return view;
    }

    void WorldManager::setViewPosition(Vector view_pos) {
        float x = view_pos.getX() - view.getHorizontal() / 2;
        if (x + view.getHorizontal() > boundary.getHorizontal()) {
            x = boundary.getHorizontal() - view.getHorizontal();
        }
        if (x < 0) {
            x = 0;
        }

        int y = view_pos.getY() - view.getVertical() / 2;
        if (y + view.getVertical() > boundary.getVertical()) {
            y = boundary.getVertical() - view.getVertical();
        }
        if (y < 0) {
            y = 0;
        }
        Vector new_corner(x, y);
        view.setCorner(new_corner);
    }
    int WorldManager::setViewFollowing(Object* p_new_view_following) {
        // Set to NULL to turn ‘off’ following.
        if (p_new_view_following == NULL) {
            p_view_following = NULL;
            return 0; // Success
        }

        // Iterate over all Objects. Make sure p_new_view_following
        // is one of the Objects, then set found to true.
        bool found = false;
        
        for (int i = 0; i < m_updates.getCount(); i++) {
            if (m_updates[i] == p_new_view_following) {
                found = true;
                break;
            }
        }


        // If found, adjust attribute accordingly and set view position.
        if (found) {
            p_view_following = p_new_view_following;
            setViewPosition(p_view_following->getPosition());
            return 0; // Success
        }

        // If we get here, p_new_view_following was not valid. Don't change current view.
        return -1; // Error
    }



}
