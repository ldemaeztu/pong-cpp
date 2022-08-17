#include "ball.hpp"

#include <algorithm>

Ball::Ball(Vec2D dim) : Object(dim), m_verticalCollision(false), m_horizontalCollision(false) {

}

Ball::~Ball() {
    
};

/** Returns if a goal has been scored given the current position of the ball */
void Ball::checkGoal(bool& goalLeftPlayer, bool& goalRightPlayer) {
    goalLeftPlayer = m_isOnLeftBound;
    goalRightPlayer = m_isOnRightBound;
}

/** Modify movement of the ball according to possible collisions */
void Ball::updateSpeed() {
    if (m_horizontalCollision)
        m_speed.x = -1.0f * m_speed.x;
    if (m_verticalCollision)
        m_speed.y = -1.0f * m_speed.y;
    if (m_isOnTopBound || m_isOnBottomBound)
        m_speed.y = -1.0f * m_speed.y;
    if (m_isOnLeftBound || m_isOnRightBound)
        m_speed.x = -1.0f * m_speed.x;
}

/** Updates the collision status of the ball for this frame */
void Ball::updateCollision(const bool horizontal, const bool vertical) {
    m_horizontalCollision = horizontal;
    m_verticalCollision = vertical;
}
