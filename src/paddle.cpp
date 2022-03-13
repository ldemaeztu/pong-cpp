#include "paddle.hpp"

#include <algorithm>

/** Anula la velocidad de todo objeto que se vaya a salir de la pantalla */
void Paddle::checkBoundaries() {
    if (getTopBoundary() <= -0.99f) {
        m_speed.y = std::max(0.0f, m_speed.y);
    }
    if (getBottomBoundary() >= 0.99f) {
        m_speed.y = std::min(0.0f, m_speed.y);
    }    
}

void Paddle::updatePosition() {
    m_position.x += m_speed.x;
    m_position.y += m_speed.y;
    m_speed = Vector2D(0.0f, 0.0f);
}