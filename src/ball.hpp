#ifndef BALL_H
#define BALL_H    

#include "object.hpp"

class Ball : public Object {
public:
    Ball() : Object() {};
    ~Ball(){};

    void checkBoundaries();
    void checkCollision(Boundaries paddleBound);
    Boundaries computeOverlap(Boundaries paddleBound, Boundaries ballBound);
    void updatePosition();    

private:


};

#endif
