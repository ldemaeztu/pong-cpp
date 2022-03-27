#include "object.hpp"    

#include <iostream>
    
    
Object::Object() : m_speed(0.0f, 0.0f), m_position(0.0f, 0.0f) {

};

Object::~Object() {

};

void Object::setPosition(const float x, const float y) {
    m_position.x = x;
    m_position.y = y;
}

void Object::setDimensions(const float w, const float h) {
    m_dimensions.w = w;
    m_dimensions.h = h;
}

Vector2D Object::getPosition() {
    return m_position;
}

Dimensions Object::getDimensions() {
    return m_dimensions;
}

void Object::setSpeed(const Vector2D speed) {
    m_speed = speed;
}

float Object::getLeftBoundary() {
    return m_position.x - m_dimensions.w/2.0f;
}

float Object::getRightBoundary() {
    return m_position.x + m_dimensions.w/2.0f;
}

float Object::getTopBoundary() {
    return m_position.y - m_dimensions.h/2.0f;
}

float Object::getBottomBoundary() {
    return m_position.y + m_dimensions.h/2.0f;
}

Boundaries Object::getBoundaries() {
    Boundaries b(getLeftBoundary(), getRightBoundary(), getTopBoundary(), getBottomBoundary());
    return b;
}

Boundaries Object::getFutureBoundaries() {
    Boundaries b(getLeftBoundary() + m_speed.x, getRightBoundary() + m_speed.x, getTopBoundary() + m_speed.y, getBottomBoundary() + m_speed.y);
    return b;
}