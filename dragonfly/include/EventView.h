#ifndef EVENTVIEW_H
#define EVENTVIEW_H

#include "Event.h"

const std::string VIEW_EVENT = "df::view";
namespace df {
    class EventView : public Event {

    private:
        std::string m_tag;  // Tag to associate.
        int m_value;        // Value for view.
        bool m_delta;       // True if change in value, else replace value.

    public:
        // Create view event with tag VIEW_EVENT, value 0, and delta false.
        EventView();

        // Create view event with tag, value, and delta as indicated.
        EventView(std::string new_tag, int new_value, bool new_delta);

        // Set tag to new_tag.
        void setTag(std::string new_tag);

        // Get tag.
        std::string getTag() const;

        // Set value to new_value.
        void setValue(int new_value);

        // Get value.
        int getValue() const;

        // Set delta to new_delta.
        void setDelta(bool new_delta);

        // Get delta.
        bool getDelta() const;
    };
}
#endif  // EVENTVIEW_H
