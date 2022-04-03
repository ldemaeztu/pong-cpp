#ifndef BALL_H
#define BALL_H    

#include "object.hpp"

class Ball : public Object {
public:
    Ball();
    ~Ball();

    void checkCollision(Boundaries paddleBound);
    Boundaries computeOverlap(Boundaries paddleBound, Boundaries ballBound);

    void modifyMovement();
    void updatePosition();

    void checkGoal(bool& goalLeftPlayer, bool& goalRightPlayer);    

private:

};

#endif
