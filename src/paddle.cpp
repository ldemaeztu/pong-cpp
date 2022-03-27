#include "paddle.hpp"

#include <algorithm>

/** Avoids that the paddles leave the screen */
void Paddle::checkBoundaries() {
    if (getTopBoundary() <= -0.99f) {
        m_speed.y = std::max(0.0f, m_speed.y);
    }
    if (getBottomBoundary() >= 0.99f) {
        m_speed.y = std::min(0.0f, m_speed.y);
    }    
}

/** Updates position according to previous position and speed */
void Paddle::updatePosition() {
    m_position.x += m_speed.x;
    m_position.y += m_speed.y;
    m_speed = Vector2D(0.0f, 0.0f);
}