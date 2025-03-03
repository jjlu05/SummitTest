// utility.h
#ifndef UTILITY_H
#define UTILITY_H

#include "Vector.h"
#include "Box.h"
#include "Object.h"

namespace df {
    bool positionsIntersect(const df::Vector& pos1, const df::Vector& pos2);
    Box getWorldBox(const Object *p_o);

    Box getWorldBox(const Object *p_o, Vector where);


    bool boxIntersectsBox(df::Box A, df::Box B);
    Vector worldToView(Vector world_pos);
    std::string toString(int i);
    Vector viewToWorld(Vector view_pos);

}

#endif 
