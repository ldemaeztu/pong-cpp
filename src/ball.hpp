#ifndef BALL_H
#define BALL_H    

#include "object.hpp"

class Ball : public Object {
public:
    Ball() : Object() {};
    ~Ball(){};

    void checkBoundaries();
    void updatePosition();

private:


};

#endif
