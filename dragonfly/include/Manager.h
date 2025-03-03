#ifndef MANAGER_H
#define MANAGER_H

#include <string>
#include "EventStep.h"
namespace df {

class Manager {
private:
    std::string m_type;   
    bool m_is_started;    

protected:
    // Set type identifier of Manager
    void setType(std::string type);

public:
    Manager();
    virtual ~Manager();

    // Get type identifier of Manager
    std::string getType() const;

    // Startup Manager
    // Return 0 if OK, else negative number
    virtual int startUp();

    // Shutdown Manager
    virtual void shutDown();

    // Return true when startUp() was executed OK, else false
    bool isStarted() const;
    //Send event to all objects
    //return count of number of events sent
    int onEvent(const Event* p_event);
};

} 

#endif  
