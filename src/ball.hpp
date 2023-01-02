#ifndef BALL_H
#define BALL_H    

#include "configloader.hpp"
#include "object.hpp"

class Ball : public Object {
public:
    Ball(ConfigLoader *config, Vec2D dim);
    ~Ball();

    void checkGoal(bool& goalLeftPlayer, bool& goalRightPlayer);    
    void checkBallPaddleCollision(Vec2D padSpeed, Segment padSideSegm, 
                                  Segment padTopSegment, Segment padBottomSegment);
    void updatePosition();
    void modifySpeed();                                      

private:
    float computeReboundAngle(Segment paddleSegment, Vec2D intersectionPoint);

private:
    bool m_vertCollision;
    bool m_horizCollision;
    float m_angle;
};

#endif
