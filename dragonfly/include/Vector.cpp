#include "Vector.h"
#include <cmath>
namespace df {

    Vector::Vector() : x(0), y(0) {


    }
    // initialization
    Vector::Vector(float init_x, float init_y) {
        x = init_x;
        y = init_y;
    };


    // Get/set horizontal component.
    void Vector::setX(float new_x) {
        x = new_x;
    };
    float Vector::getX() const {
        return x;
    };

    // Get/set vertical component.
    void Vector::setY(float new_y) {
        y = new_y;
    };
    float Vector::getY() const {
        return y;
    };

    // Set horizontal & vertical components.
    void Vector::setXY(float new_x, float new_y) {
        x = new_x;
        y = new_y;
    };

    // Return magnitude of vector.
    float Vector::getMagnitude() const {
        float mag = sqrt(x * x + y * y);
        return mag;
    }

    // Scale vector.
    void Vector::scale(float s) {
        x = x * s;
        y = y * s;
    }

    // Normalize vector.
    void Vector::normalize() {
        float length = getMagnitude();
        if (length > 0) {
            x = x / length;
            y = y / length;
        }
    }

    // Add two Vectors, return new Vector.
    Vector Vector::operator +(const Vector& other) const {
        Vector v;  
        v.x = x + other.x; 
        v.y = y + other.y; 
        return v; // Return new vector.
    }
}