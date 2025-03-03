#ifndef WORLD_MANAGER_H
#define WORLD_MANAGER_H
#include "Manager.h"
#include "ObjectList.h"
#define WM df::WorldManager::getInstance()
namespace df {
    const int MAX_ALTITUDE = 4;

    class WorldManager : public Manager {

    private:
        WorldManager(); // Private (as singleton).
        WorldManager(WorldManager const&); // Don't allow copy.
        void operator=(WorldManager const&); // Don't allow assignment.
        Box boundary;
        Box view;
        Object* p_view_following;

        ObjectList m_updates; // All Objects in world to update.
        ObjectList m_deletions; // All Objects in world to delete.

    public:
        // Get the one and only instance of the WorldManager.
        static WorldManager& getInstance();

        // Startup game world (initialize everything to empty).
        // Return 0.
        int startUp();

        // Shutdown game world (delete all game world Objects).
        void shutDown();

        // Insert Object into world. Return 0 if ok, else -1.
        int insertObject(Object* p_o);

        // Remove Object from world. Return 0 if ok, else -1.
        int removeObject(Object* p_o);

        // Return list of all Objects in world.
        ObjectList getAllObjects() const;

        // Return list of all Objects in world matching type.
        ObjectList objectsOfType(std::string type) const;

        // Update world.
        // Delete Objects marked for deletion.
        void update();

        // Indicate Object is to be deleted at end of current game loop.
        // Return 0 if ok, else -1.
        int markForDelete(Object* p_o);

        void draw();
        ObjectList getCollisions(const Object* p_o, Vector where);
        int moveObject(Object* p_o, Vector where);


        void setBoundary(Box new_boundary);
        Box getBoundary() const;
        void setView(Box new_view);
        Box getView() const;

        void setViewPosition(Vector view_pos);
        int setViewFollowing(Object* p_new_view_following);


    };
}
#endif // WORLD_MANAGER_H
