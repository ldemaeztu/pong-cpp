#ifndef BALL_H
#define BALL_H    

#include "object.hpp"

class Ball : public Object {
public:
    Ball(Vec2D dim);
    ~Ball();

    void checkGoal(bool& goalLeftPlayer, bool& goalRightPlayer);    
    void updateSpeed();
    void updateCollision(const bool horizontal, const bool vertical);

private:
    bool m_verticalCollision;
    bool m_horizontalCollision;
};

#endif
