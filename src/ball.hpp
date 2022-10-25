#ifndef BALL_H
#define BALL_H    

#include "object.hpp"

#define SPEED_UNIT 0.02f

class Ball : public Object {
public:
    Ball(Vec2D dim);
    ~Ball();

    void checkGoal(bool& goalLeftPlayer, bool& goalRightPlayer);    
    void updateSpeed();
    void updateCollision(const bool horizontal, const bool vertical, const float angle);

private:
    bool m_verticalCollision;
    bool m_horizontalCollision;
    float m_angle;
};

#endif
