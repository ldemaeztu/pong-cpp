#include "object.h"    
    
    
Object::Object() : m_speed(0.0f) {

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

void Object::setSpeed(float speed) {
    m_speed = speed;
}

void Object::updatePosition() {
    m_position.y += m_speed / 40.0f;
    m_speed = 0.0f;
}