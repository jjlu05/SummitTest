#include "Event.h"

namespace df {
    const std::string OUT_EVENT = "df::out";

    class EventOut : public df::Event {
    public:
        EventOut();
    };
}
