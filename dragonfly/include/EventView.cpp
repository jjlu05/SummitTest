#include "EventView.h"
namespace df {
    // Default constructor: Initializes with VIEW_EVENT, value 0, and delta false.
    EventView::EventView(){
        setType(VIEW_EVENT);
        //NEED OR NOT
        //NEED OR NOT?
        m_tag = VIEW_EVENT;
        m_value = 0;
        m_delta = false;
    }

    // Parameterized constructor: Initializes with given tag, value, and delta.
    EventView::EventView(std::string new_tag, int new_value, bool new_delta) {
        setType(VIEW_EVENT);

        m_tag = new_tag;
        m_value = new_value;
        m_delta = new_delta;
    }

    // Set tag to new_tag.
    void EventView::setTag(std::string new_tag) {
        m_tag = new_tag;
    }

    // Get tag.
    std::string EventView::getTag() const {
        return m_tag;
    }

    // Set value to new_value.
    void EventView::setValue(int new_value) {
        m_value = new_value;
    }

    // Get value.
    int EventView::getValue() const {
        return m_value;
    }

    // Set delta to new_delta.
    void EventView::setDelta(bool new_delta) {
        m_delta = new_delta;
    }

    // Get delta.
    bool EventView::getDelta() const {
        return m_delta;
    }
}