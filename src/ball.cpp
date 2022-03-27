#include "ball.hpp"

#include <algorithm>

/** Makes ball rebound on screen boundaries */
void Ball::checkBoundaries() {
    if (getTopBoundary() <= -0.99f)
        m_speed.y = -1.0f * m_speed.y;
    if (getBottomBoundary() >= 0.99f)
        m_speed.y = -1.0f * m_speed.y;
    if (getLeftBoundary() <= -0.99f)
        m_speed.x = -1.0f * m_speed.x;
    if (getRightBoundary() >= 0.99f)
        m_speed.x = -1.0f * m_speed.x;
}

/** 
 * Checks if there is a collision between the ball and a paddle.
 * If so, it modifies the speed of the ball.
 */
void Ball::checkCollision(Boundaries paddleBound) {
    Boundaries ballBound = getFutureBoundaries();
    Boundaries overlap = computeOverlap(paddleBound, ballBound);
    // If there is overlap between ball and paddle decide if it corresponds to 
    // an horizontal or vertical rebound
    if (overlap.area() > 0.0f) {
        // Compute future ball position and overlap with the paddle if we decide to modify the horizontal speed
        Vector2D speed1(-1.0f * m_speed.x, m_speed.y);
        Boundaries ballBoundaries1(ballBound.l + speed1.x, ballBound.r + speed1.x, ballBound.t + speed1.y, ballBound.b + speed1.y);
        Boundaries overlap1 = computeOverlap(paddleBound, ballBoundaries1);
        // Compute future ball position and overlap with the paddle if we decide to modify the vertical speed
        Vector2D speed2(m_speed.x, -1.0f * m_speed.y);
        Boundaries ballBoundaries2(ballBound.l + speed2.x, ballBound.r + speed2.x, ballBound.t + speed2.y, ballBound.b + speed2.y);
        Boundaries overlap2 = computeOverlap(paddleBound, ballBoundaries2);
        // Modify the speed of the ball that produces the smallest overlap between paddle and ball in the future step
        if (overlap1.area() < overlap2.area())
            m_speed = speed1;
        else
            m_speed = speed2;
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

/** Updates position according to previous position and speed */
void Ball::updatePosition() {
    m_position.x += m_speed.x;
    m_position.y += m_speed.y;
}
