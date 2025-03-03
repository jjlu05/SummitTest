#include "Box.h"
namespace df {
    // Default constructor.
    Box::Box() : m_corner(Vector()), m_horizontal(0), m_vertical(0) {}

    // Constructor with specified values.
    Box::Box(Vector init_corner, float init_horizontal, float init_vertical)
        : m_corner(init_corner), m_horizontal(init_horizontal), m_vertical(init_vertical) {}

    // Set upper-left corner of the box.
    void Box::setCorner(Vector new_corner) {
        m_corner = new_corner;
    }

    // Get upper-left corner of the box.
    Vector Box::getCorner() const {
        return m_corner;
    }

    // Set horizontal size of the box.
    void Box::setHorizontal(float new_horizontal) {
        m_horizontal = new_horizontal;
    }

    // Get horizontal size of the box.
    float Box::getHorizontal() const {
        return m_horizontal;
    }

    // Set vertical size of the box.
    void Box::setVertical(float new_vertical) {
        m_vertical = new_vertical;
    }

    // Get vertical size of the box.
    float Box::getVertical() const {
        return m_vertical;
    }
}