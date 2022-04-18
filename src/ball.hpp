#ifndef BALL_H
#define BALL_H    

#include "object.hpp"

class Ball : public Object {
public:
    Ball(Vec2D dim);
    ~Ball();

    void checkPaddlesCollision(Boundaries paddleBoundL, Boundaries paddleBoundR);
    Boundaries computeOverlap(Boundaries paddleBound, Boundaries ballBound);
    void checkGoal(bool& goalLeftPlayer, bool& goalRightPlayer);    

    void modifySpeed();

private:
    void checkPaddleCollision(Boundaries paddleBound, bool& verticalCollision, bool& horizontalCollision);

private:
    bool m_verticalCollision;
    bool m_horizontalCollision;
};

#endif
