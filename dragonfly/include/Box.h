#ifndef DF_BOX_H
#define DF_BOX_H
#include "Vector.h"
namespace df {
    class Box {
    private:
        Vector m_corner;      // Upper-left corner of the box.
        float m_horizontal;   // Horizontal dimension.
        float m_vertical;     // Vertical dimension.

    public:
        // Create box with (0,0) for the corner, and 0 for horizontal and vertical sizes.
        Box();

        // Create box with an upper-left corner, horizontal and vertical sizes.
        Box(Vector init_corner, float init_horizontal, float init_vertical);

        // Set upper-left corner of the box.
        void setCorner(Vector new_corner);

        // Get upper-left corner of the box.
        Vector getCorner() const;

        // Set horizontal size of the box.
        void setHorizontal(float new_horizontal);

        // Get horizontal size of the box.
        float getHorizontal() const;

        // Set vertical size of the box.
        void setVertical(float new_vertical);

        // Get vertical size of the box.
        float getVertical() const;
    };
}
#endif