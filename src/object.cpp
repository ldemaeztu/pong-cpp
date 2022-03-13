#include "object.hpp"    

#include <iostream>
    
    
Object::Object() : m_speed(0.0f, 0.0f), m_position(0.0f, 0.0f) {

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

Vector2D Object::getPosition() {
    return m_position;
}

Dimensions Object::getDimensions() {
    return m_dimensions;
}

void Object::setSpeed(Vector2D speed) {
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