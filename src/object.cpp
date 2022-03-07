#include "object.hpp"    

#include <iostream>
    
    
Object::Object(bool continuousMovement) : m_speed(0.0, 0.0f), m_continuousMovement(continuousMovement) {

};

Object::~Object() {

};

void Object::setPosition(float x, float y) {
    m_position.x = x;
    m_position.y = y;
}

void Object::setDimensions(float w, float h) {
    m_dimensions.w = w;
    m_dimensions.h = h;
}

Position Object::getPosition() {
    return m_position;
}

Dimensions Object::getDimensions() {
    return m_dimensions;
}

void Object::setSpeed(Speed speed) {
    m_speed = speed;
}

void Object::updatePosition() {
    m_position.x += m_speed.x;
    m_position.y += m_speed.y;
    if (!m_continuousMovement) {
        m_speed.x = 0.0f;
        m_speed.y = 0.0f;
    }
}

void Object::forceYPosition(float y) {
    m_position.y = y;
}