#include "geometry.hpp"

#include <iostream>
#include <limits>

#define EPSILON 0.00000001f

/*
 * Compute intersection point between segments (p1, p2) and (p3, p4). 
 *  If no intersection point, quiet_NaN coordinates are returned.
 */ 
Vec2D Geometry::computeSegmentsIntersection(Segment s1, Segment s2) {
    Vec2D pi(std::numeric_limits<float>::quiet_NaN(), 
        std::numeric_limits<float>::quiet_NaN());
    Vec2D p1 = s1.p1;
    Vec2D p2 = s1.p2;
    Vec2D p3 = s2.p1;
    Vec2D p4 = s2.p2;
    // Assign x and y values to simplify notation
    float x1 = p1.x, x2 = p2.x, x3 = p3.x, x4 = p4.x;
    float y1 = p1.y, y2 = p2.y, y3 = p3.y, y4 = p4.y;
    // Compute the intersection point parameters
    float t = ((x1 - x3) * (y3 - y4) - (y1 - y3) * (x3 - x4)) /
        ((x1 - x2) * (y3 - y4) - (y1 - y2) * (x3 - x4));
     float u = ((x1 - x3) * (y1 - y2) - (y1 - y3) * (x1 - x2)) /
         ((x1 - x2) * (y3 - y4) - (y1 - y2) * (x3 - x4));
    if (t >= 0.0f && t <= 1.0f && u >= 0.0f && u <= 1.0f) {
        pi.x = x1 + t * (x2 - x1);
        pi.y = y1 + t * (y2 - y1);
    }
    return pi;
}


