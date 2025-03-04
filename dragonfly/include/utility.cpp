#include "utility.h"
#include <cmath>  
#include "Object.h"
#include "WorldManager.h"
#include <sstream>
#include <iostream>
namespace df {
    bool positionsIntersect(const df::Vector& p1, const df::Vector& p2) {
        // if the absolute differences in x and y are <= 1, then the positions intersect
        return (std::fabs(p1.getX() - p2.getX()) <= 1 &&
            std::fabs(p1.getY() - p2.getY()) <= 1);
    }


    bool boxIntersectsBox(df::Box A, df::Box B) {
        // Get the corner positions
        float Ax1 = A.getCorner().getX();
        float Ay1 = A.getCorner().getY();
        float Ax2 = Ax1 + A.getHorizontal();
        float Ay2 = Ay1 + A.getVertical();

        float Bx1 = B.getCorner().getX();
        float By1 = B.getCorner().getY();
        float Bx2 = Bx1 + B.getHorizontal();
        float By2 = By1 + B.getVertical();

        // Check horizontal overlap
        bool x_overlap = (Bx1 <= Ax1 && Ax1 <= Bx2) || (Ax1 <= Bx1 && Bx1 <= Ax2);

        // Check vertical overlap
        bool y_overlap = (By1 <= Ay1 && Ay1 <= By2) || (Ay1 <= By1 && By1 <= Ay2);

        // Boxes intersect if both x and y overlap
        return x_overlap && y_overlap;
    }


    Box getWorldBox(const Object *p_o)
    {
        return getWorldBox(p_o, p_o->getPosition());
    }
    Box getWorldBox(const Object* p_o, Vector where) {
        // Get the object's relative bounding box
        Box box = p_o->getBox();

        // Adjust the box's corner to world position
        Vector corner = box.getCorner();
        corner.setX(corner.getX() + where.getX());
        corner.setY(corner.getY() + where.getY());
        box.setCorner(corner);

        return box;

    }

  
    // Convert world position to view position.
    Vector worldToView(Vector world_pos) {
        // Get the view's top-left corner (origin) in world coordinates.
        Vector view_origin = WM.getView().getCorner();
        int view_x = view_origin.getX();
        int view_y = view_origin.getY();
        // Compute the object's position relative to the view.
        Vector view_pos(world_pos.getX() - view_x,
            world_pos.getY() - view_y);

        return view_pos;
    }


    // Convert view position to world position.
    Vector viewToWorld(Vector view_pos) {
        // Get the view's top-left corner (origin) in world coordinates.
        Vector view_origin = WM.getView().getCorner();
         // Compute the object's position in world space.
        Vector world_pos(view_pos.getX() + view_origin.getX(),
            view_pos.getY() + view_origin.getY());

        return world_pos;
    }




     using std::stringstream;
    
      std::string toString(int i) {
      std::stringstream ss; 
      ss << i;  
      return ss.str(); 
    }

}