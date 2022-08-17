#include "paddle.hpp"

#include <algorithm>

Paddle::Paddle(Vec2D dim) : Object(dim), m_score(0) {
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
void Paddle::updateSpeed() {
    if (m_isOnTopBound)
        m_speed.y = std::max(0.0f, m_speed.y);
    if (m_isOnBottomBound)
        m_speed.y = std::min(0.0f, m_speed.y);
}