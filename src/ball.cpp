#include "ball.hpp"

#include <algorithm>
#include <cmath>
#include <iostream>

#include "geometry.hpp"

Ball::Ball(ConfigLoader* config, Vec2D dim) : Object(config, dim),
                                              m_vertCollision(false), 
                                              m_horizCollision(false) {
}

Ball::~Ball() {
};

/** Returns if a goal has been scored given the current position of the ball */
void Ball::checkGoal(bool& goalLeftPlayer, bool& goalRightPlayer) {
    goalLeftPlayer = m_isOnLeftBound;
    goalRightPlayer = m_isOnRightBound;
}


/** Checks if there is a collision between the ball and a paddle */
void Ball::checkBallPaddleCollision(Vec2D padSpeed, Segment padSideSegm, 
                                    Segment padTopSegment, Segment padBottomSegment) {
    Vec2D ballPosition = m_position;
    Vec2D ballSpeed = m_speed;

    // Compute a line that describes relative ball-paddle motion
    Vec2D ballInitialPoint = ballPosition;
    Vec2D ballFinalPoint = ballPosition + ballSpeed - padSpeed;
    Segment ballSegment(ballInitialPoint, ballFinalPoint);

    // Intersect this line with the boundaries of the paddle (check collision)
    Vec2D intersectionSide = 
        Geometry::computeSegmentsIntersection(ballSegment, padSideSegm);
    Vec2D intersectionTop = 
        Geometry::computeSegmentsIntersection(ballSegment, padTopSegment);
    Vec2D intersectionBottom = 
        Geometry::computeSegmentsIntersection(ballSegment, padBottomSegment);

    // Decide if there has been a collision with the side of the paddle (horizontal)
    // or with the top or bottom of the paddle (vertical)
    m_horizCollision = !std::isnan(intersectionSide.x);
    m_vertCollision = (!std::isnan(intersectionTop.x) && ballSpeed.y > 0) ||
                      (!std::isnan(intersectionBottom.x) && ballSpeed.y < 0);

    // If there is an horizontal collision, compute the rebound angle
    if (m_horizCollision)
    {
        m_angle = computeReboundAngle(padSideSegm, intersectionSide);
        // If it's the right paddle, correct the angle
        if (!isOnLeftHalf())
            m_angle = m_angle >= 0.0 ? std::numbers::pi - m_angle : 
                                       -std::numbers::pi - m_angle;

    }
}

/** Computes the rebound angle after an horizontal paddle-ball collision */
float Ball::computeReboundAngle(Segment paddleSegment, Vec2D intersectionPoint) {
    // Compute the relative position of the intersection point in the paddle segment
    float middlePointY = (paddleSegment.p1.y + paddleSegment.p2.y) / 2.0;
    float length = std::abs(paddleSegment.p1.y - paddleSegment.p2.y) / 2.0;
    float horizontalCollisionPosition = (intersectionPoint.y - middlePointY) / length;

    // Transform collision position to rebound angle
    float divisor = m_config->get<float>("g", "angle_divisor");
    float angle = horizontalCollisionPosition * std::numbers::pi / divisor;
    
    return angle;
}

/** Modifies movement of the ball given collision info */
void Ball::modifySpeed() {
    // Paddle-ball collisions
    if (m_horizCollision) 
    {
        m_speed.x = m_config->get<float>("g", "speed_unit") * cos(m_angle);
        m_speed.y = m_config->get<float>("g", "speed_unit") * sin(m_angle);
    }
    if (m_vertCollision)
        m_speed.y = -1.0f * m_speed.y;

    // Screen boundaries-ball collisions
    if (m_isOnTopBound || m_isOnBottomBound)
        m_speed.y = -1.0f * m_speed.y;
    if (m_isOnLeftBound || m_isOnRightBound)
        m_speed.x = -1.0f * m_speed.x;
}

/** Updates ball position */
void Ball::updatePosition() {
    m_position.x += m_speed.x;
    m_position.y += m_speed.y;
}
