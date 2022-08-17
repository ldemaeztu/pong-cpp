#ifndef GEOMETRY_H
#define GEOMETRY_H    
 
#include "object.hpp"

class Geometry {
public:
    static Vec2D computeSegmentsIntersection(Segment s1, Segment s2);
};

#endif
