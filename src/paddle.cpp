#include "paddle.hpp"

#include <algorithm>

Paddle::Paddle(ConfigLoader *config, Vec2D dim) : Object(config, dim), m_score(0) {
}

Paddle::~Paddle() {
    
}

/** Returns the score for this player */
int Paddle::getScore() {
    return m_score;
}

/** Adds one point to the player that controls this paddle */
void Paddle::addOnePoint() {
    m_score++;
}

/** Stop the paddle if it has reached a screen boundary */
void Paddle::modifySpeed() {
    if (m_isOnTopBound)
        m_speed.y = std::max(0.0f, m_speed.y);
    if (m_isOnBottomBound)
        m_speed.y = std::min(0.0f, m_speed.y);
}

/** Updates paddle position and resets speed (it will be set again if a key is pressed) */
void Paddle::updatePosition() {
    m_position.x += m_speed.x;
    m_position.y += m_speed.y;
    m_speed.x = 0.0f;
    m_speed.y = 0.0f;
}