#include "ball.hpp"

#include <algorithm>

Ball::Ball(Vec2D dim) : Object(dim), m_verticalCollision(false), m_horizontalCollision(false) {

}

Ball::~Ball() {
    
};

/** Checks if there is a collision between the ball and any paddle */
void Ball::checkPaddlesCollision(Boundaries paddleBoundL, Boundaries paddleBoundR) {
    // Check collision between left paddle and ball
    bool verticalCollisionPaddleL, horizontalCollisionPaddleL;
    checkPaddleCollision(paddleBoundL, verticalCollisionPaddleL, horizontalCollisionPaddleL);
    // Check collision between right paddle and ball
    bool verticalCollisionPaddleR, horizontalCollisionPaddleR;
    checkPaddleCollision(paddleBoundR, verticalCollisionPaddleR, horizontalCollisionPaddleR);
    // Combine results of paddle left and paddle right collisions check
    m_verticalCollision = verticalCollisionPaddleL || verticalCollisionPaddleR;
    m_horizontalCollision = horizontalCollisionPaddleL || horizontalCollisionPaddleR;
}

/** Checks if there is a vertical or horizontal collision between the ball and a paddle */
void Ball::checkPaddleCollision(Boundaries paddleBound, bool& verticalCollision, bool& horizontalCollision) {
    verticalCollision = false;
    horizontalCollision = false;
    Boundaries ballBound = getFutureBoundaries();
    Boundaries overlap = computeOverlap(paddleBound, ballBound);
    // If there is overlap between ball and paddle decide if it corresponds to 
    // an horizontal or vertical rebound
    if (overlap.area() > 0.0f) {
        // Compute future ball position and overlap with the paddle if we decide to modify the horizontal speed
        Vec2D speed1(-1.0f * m_speed.x, m_speed.y);
        Boundaries ballBoundaries1(ballBound.l + speed1.x, ballBound.r + speed1.x, ballBound.t + speed1.y, ballBound.b + speed1.y);
        Boundaries overlap1 = computeOverlap(paddleBound, ballBoundaries1);
        // Compute future ball position and overlap with the paddle if we decide to modify the vertical speed
        Vec2D speed2(m_speed.x, -1.0f * m_speed.y);
        Boundaries ballBoundaries2(ballBound.l + speed2.x, ballBound.r + speed2.x, ballBound.t + speed2.y, ballBound.b + speed2.y);
        Boundaries overlap2 = computeOverlap(paddleBound, ballBoundaries2);
        // Modify the speed of the ball that produces the smallest overlap between paddle and ball in the future step
        if (overlap1.area() < overlap2.area())
            horizontalCollision = true;
        else
            verticalCollision = true;
    }
}

/** Computes the overlap between the paddle and the ball */
Boundaries Ball::computeOverlap(Boundaries paddleBound, Boundaries ballBound) {
    Boundaries overlap(std::max(paddleBound.l, ballBound.l),
        std::min(paddleBound.r, ballBound.r),
        std::max(paddleBound.t, ballBound.t),
        std::min(paddleBound.b, ballBound.b));
    return overlap;
}

/** Returns if a goal has been scored given the current position of the ball */
void Ball::checkGoal(bool& goalLeftPlayer, bool& goalRightPlayer) {
    goalLeftPlayer = m_isOnLeftBound;
    goalRightPlayer = m_isOnRightBound;
}

/** Modify movement of the ball according to possible collisions */
void Ball::modifySpeed() {
    if (m_horizontalCollision)
        m_speed.x = -1.0f * m_speed.x;
    if (m_verticalCollision)
        m_speed.y = -1.0f * m_speed.y;
    if (m_isOnTopBound || m_isOnBottomBound)
        m_speed.y = -1.0f * m_speed.y;
    if (m_isOnLeftBound || m_isOnRightBound)
        m_speed.x = -1.0f * m_speed.x;
}
