#include "object.hpp"    

#include <iostream>
    
Object::Object() : m_speed(0.0f, 0.0f), m_position(0.0f, 0.0f), m_dimensions(0.0f, 0.0f), 
    m_isOnTopBound(false), m_isOnBottomBound(false), m_isOnLeftBound(false), m_isOnRightBound(false) {
};    
    
Object::Object(Vec2D dim) : m_speed(0.0f, 0.0f), m_position(0.0f, 0.0f), m_dimensions(dim), 
    m_isOnTopBound(false), m_isOnBottomBound(false), m_isOnLeftBound(false), m_isOnRightBound(false) {
};

Object::~Object() {
};

/** Returns object's central position */
Vec2D Object::getPosition() {
    return m_position;
}

/** Returns object's speed */
Vec2D Object::getSpeed() {
    return m_speed;
}

/** Sets object's dimensions */
void Object::setDimensions(const float w, const float h) {
    m_dimensions.x = w;
    m_dimensions.y = h;
}

/** Sets object's central position */
void Object::setPosition(const float x, const float y) {
    m_position.x = x;
    m_position.y = y;
}

/** Sets the object's speed */
void Object::setSpeed(const Vec2D speed) {
    m_speed = speed;
}

/** Returns object's boundaries */
Boundaries Object::getBoundaries() {
    Boundaries b(getLeftBoundary(), getRightBoundary(), getTopBoundary(), getBottomBoundary());
    return b;
}

/** Returns x coordinate of the left boundary of the object */
float Object::getLeftBoundary() {
    return m_position.x - m_dimensions.x/2.0f;
}

/** Returns x coordinate of the right boundary of the object */
float Object::getRightBoundary() {
    return m_position.x + m_dimensions.x/2.0f;
}

/** Returns y coordinate of the top boundary of the object */
float Object::getTopBoundary() {
    return m_position.y - m_dimensions.y/2.0f;
}

/** Returns y coordinate of the bottom boundary of the object */
float Object::getBottomBoundary() {
    return m_position.y + m_dimensions.y/2.0f;
}

/** Returns object's segments */
void Object::getSegments(Segment& leftSegment, Segment& rightSegment, Segment& topSegment, Segment& bottomSegment) {
    Boundaries boundaries = getBoundaries();
    leftSegment = Segment(Vec2D(boundaries.l, boundaries.t), Vec2D(boundaries.l, boundaries.b));
    rightSegment = Segment(Vec2D(boundaries.r, boundaries.t), Vec2D(boundaries.r, boundaries.b));
    topSegment = Segment(Vec2D(boundaries.l, boundaries.t), Vec2D(boundaries.r, boundaries.t));
    bottomSegment = Segment(Vec2D(boundaries.l, boundaries.b), Vec2D(boundaries.r, boundaries.b));    
}

/** Checks if object is over any of the screen boundaries */
void Object::checkIsOnBoundaries() {
    m_isOnTopBound = isOnTopBoundary();
    m_isOnBottomBound = isOnBottomBoundary();
    m_isOnLeftBound = isOnLeftBoundary();
    m_isOnRightBound = isOnRightBoundary();
}

/** Checks if object is over the top screen boundary */
bool Object::isOnTopBoundary() {
    return getTopBoundary() <= -SCREEN_LIMIT;
}

/** Checks if object is over the bottom screen boundary */
bool Object::isOnBottomBoundary() {
    return getBottomBoundary() >= SCREEN_LIMIT;
}

/** Checks if object is over the left screen boundary */
bool Object::isOnLeftBoundary() {
    return getLeftBoundary() <= -SCREEN_LIMIT;
}

/** Checks if object is over the right screen boundary */
bool Object::isOnRightBoundary() {
    return getRightBoundary() >= SCREEN_LIMIT;
}

/** Updates object position */
void Object::updatePosition() {
    m_position.x += m_speed.x;
    m_position.y += m_speed.y;
}