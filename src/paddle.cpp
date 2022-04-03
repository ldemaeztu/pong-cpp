#include "paddle.hpp"

#include <algorithm>

Paddle::Paddle() : m_score(0) {

}

Paddle::~Paddle() {
    
}

void Paddle::modifyMovement() {
    if (m_isOnTopBound)
        m_speed.y = std::max(0.0f, m_speed.y);
    if (m_isOnBottomBound)
        m_speed.y = std::min(0.0f, m_speed.y);
}

/** Updates position according to previous position and speed */
void Paddle::updatePosition() {
    m_position.x += m_speed.x;
    m_position.y += m_speed.y;
    m_speed = Vector2D(0.0f, 0.0f);
}

/** Returns the score for this player */
int Paddle::getScore() {
    return m_score;
}

/** Returns the score for this player */
void Paddle::addOnePoint() {
    m_score++;
}