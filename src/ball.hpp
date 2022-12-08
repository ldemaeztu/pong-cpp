#ifndef BALL_H
#define BALL_H    

#include "configloader.hpp"
#include "object.hpp"

class Ball : public Object {
public:
    Ball(ConfigLoader *configManager, Vec2D dim);
    ~Ball();

    void checkGoal(bool& goalLeftPlayer, bool& goalRightPlayer);    
    void updateSpeed();
    void updateCollision(const bool horizontal, const bool vertical, const float angle);

private:
    bool m_verticalCollision;
    bool m_horizontalCollision;
    float m_angle;

    ConfigLoader* m_config;
};

#endif
