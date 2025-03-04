#include "ViewObject.h"
#include "WorldManager.h"
#include "utility.h"
#include "DisplayManager.h"
#include "EventView.h"
#include "iostream"
namespace df {
    // Constructor
    ViewObject::ViewObject() {
        // Initialize Object attributes
        setSolidness(SPECTRAL);
        setAltitude(MAX_ALTITUDE);
        setType("ViewObject");

        // Initialize ViewObject attributes
        setValue(0);
        setDrawValue(true);
        setBorder(true);
        setLocation(TOP_CENTER);
        setColor(COLOR_DEFAULT);
        std::cout << "TSCALLED";
        // Register interest in view events
    }

    int ViewObject::draw() {
        // Construct the string to display
        std::string temp_str;
        if (m_border) {
            temp_str = " " + getViewString() + " " + toString(m_value) + " ";
        }
        else {
            temp_str = getViewString() + " " + toString(m_value);
        }

        // Convert the view position to world position
        Vector pos = viewToWorld(getPosition());

        // Draw the string at the computed position
        DM.drawString(pos, temp_str, CENTER_JUSTIFIED, getColor());      
        if (m_border) {
            Vector top_left = pos + Vector(-1, -1);
            Vector bottom_right = pos + Vector(temp_str.length(), 1);

            for (int x = top_left.getX(); x <= bottom_right.getX(); x++) {
                DM.drawCh(Vector(x, top_left.getY()), '-', m_color);  // Top border
                DM.drawCh(Vector(x, bottom_right.getY()), '-', m_color);  // Bottom border
            }
            for (int y = top_left.getY(); y <= bottom_right.getY(); y++) {
                DM.drawCh(Vector(top_left.getX(), y), '|', m_color);  // Left border
                DM.drawCh(Vector(bottom_right.getX(), y), '|', m_color);  // Right border
            }
            DM.drawCh(top_left, '+', m_color);  // Top-left corner
            DM.drawCh(Vector(bottom_right.getX(), top_left.getY()), '+', m_color);  // Top-right corner
            DM.drawCh(Vector(top_left.getX(), bottom_right.getY()), '+', m_color);  // Bottom-left corner
            DM.drawCh(bottom_right, '+', m_color);  // Bottom-right corner
        }

        return 0;
    }

    // Handle events
    int ViewObject::eventHandler(const Event* p_e) {
        if (p_e->getType() == VIEW_EVENT) {

            // Cast event to EventView
            const EventView* p_view_event = dynamic_cast<const EventView*>(p_e);
            if (!p_view_event) {
                return 0; // Failed cast, ignore event
            }

            // Only process event if the tag matches this ViewObject's view string
            if (p_view_event->getTag() == view_string) {

                // If delta is true, add value, otherwise replace it
                if (p_view_event->getDelta()) {
                    m_value += p_view_event->getValue();
                }
                else {
                    m_value = p_view_event->getValue();
                }

                return 0; // Event handled
            }
        }
        return -1; // Event not handled
    }


    // Set location
    void ViewObject::setLocation(ViewObjectLocation new_location) {
        if (new_location == UNDEFINED) return;

        Vector p;
        int y_delta = 0;

        // Get world dimensions
        int world_width = WorldManager::getInstance().getView().getHorizontal();
        int world_height = WorldManager::getInstance().getView().getVertical();

        switch (new_location) {
        case TOP_LEFT:
            p.setXY(world_width * 1 / 6, 1);
            if (!getBorder()) y_delta = -1;
            break;
        case TOP_CENTER:
            p.setXY(world_width * 3 / 6, 1);
            if (!getBorder()) y_delta = -1;
            break;
        case TOP_RIGHT:
            p.setXY(world_width * 5 / 6, 1);
            if (!getBorder()) y_delta = -1;
            break;
        case CENTER_LEFT:
            p.setXY(world_width * 1 / 6, world_height / 2);
            break;
        case CENTER_CENTER:
            p.setXY(world_width * 3 / 6, world_height / 2);
            break;
        case CENTER_RIGHT:
            p.setXY(world_width * 5 / 6, world_height / 2);
            break;
        case BOTTOM_LEFT:
            p.setXY(world_width * 1 / 6, world_height - 1);
            if (!getBorder()) y_delta = 1;
            break;
        case BOTTOM_CENTER:
            p.setXY(world_width * 3 / 6, world_height - 1);
            if (!getBorder()) y_delta = 1;
            break;
        case BOTTOM_RIGHT:
            p.setXY(world_width * 5 / 6, world_height - 1);
            if (!getBorder()) y_delta = 1;
            break;
        default:
            return;
        }

        p.setY(p.getY() + y_delta);
        setPosition(p);
        m_location = new_location;
    }

    // Get location
    ViewObjectLocation ViewObject::getLocation() const {
        return m_location;
    }

    // Set value
    void ViewObject::setValue(int new_value) {
        m_value = new_value;
    }

    // Get value
    int ViewObject::getValue() const {
        return m_value;
    }

    // Set border
    void ViewObject::setBorder(bool new_border) {
        m_border = new_border;
    }

    // Get border
    bool ViewObject::getBorder() const {
        return m_border;
    }

    // Set color
    void ViewObject::setColor(Color new_color) {
        m_color = new_color;
    }

    // Get color
    Color ViewObject::getColor() const {
        return m_color;
    }

    // Set view string
    void ViewObject::setViewString(std::string new_view_string) {
        view_string = new_view_string;
    }

    // Get view string
    std::string ViewObject::getViewString() const {
        return view_string;
    }

    // Set draw value
    void ViewObject::setDrawValue(bool new_draw_value) {
        m_draw_value = new_draw_value;
    }

    // Get draw value
    bool ViewObject::getDrawValue() const {
        return m_draw_value;
    }
}