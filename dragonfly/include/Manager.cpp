#include "Manager.h"
#include "Object.h"
#include "WorldManager.h"

namespace df {

    // Constructor
    Manager::Manager() {
        m_is_started = false;
    }

    // Destructor
    Manager::~Manager() {
        shutDown();
    }

    // Set type identifier
    void Manager::setType(std::string type) {
        m_type = type;
    }

    // Get type identifier
    std::string Manager::getType() const {
        return m_type;
    }

    // Startup Manager
    int Manager::startUp() {
        m_is_started = true;
        return 0;
    }

    // Shutdown Manager
    void Manager::shutDown() {
        m_is_started = false;
    }

    // Check if started
    bool Manager::isStarted() const {
        return m_is_started;
    }
    int Manager::onEvent(const Event* p_event) {
        int count = 0;

        ObjectList all_objects = WM.getAllObjects();
        for (int i = 0; i < all_objects.getCount(); i++) {
            all_objects[i]->eventHandler(p_event);
            count++;
        }
        return count;
    }

} // end namespace df
