#include "ball.hpp"

/** Anula la velocidad de todo objeto que se vaya a salir de la pantalla */
void Ball::checkBoundaries() {
}

void Ball::updatePosition() {
    m_position.x += m_speed.x;
    m_position.y += m_speed.y;
}