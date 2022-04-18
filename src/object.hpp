#ifndef OBJECT_H
#define OBJECT_H    

#include <algorithm>

#define SCREEN_LIMIT 0.99f

struct Boundaries
{
    Boundaries(const float l_, const float r_, const float t_, const float b_) : l(l_), r(r_), t(t_), b(b_) {};
    float area() {return std::max(0.0f, r - l) * std::max(0.0f, b - t);}
    float l; // Left
    float r; // Right
    float t; // Top
    float b; // Bottom
};


struct Vec2D
{
    Vec2D(const float x_, const float y_) : x(x_), y(y_) {};
    float x;
    float y;
};

class Object {
public:
    Object(Vec2D dim);
    ~Object();

    // Get object properties
    Vec2D getPosition();
    Boundaries getBoundaries();
    Boundaries getFutureBoundaries();
    float getLeftBoundary();
    float getRightBoundary();
    float getTopBoundary();
    float getBottomBoundary();

    // Set object properties
    void setPosition(const float x, const float y);
    void setSpeed(const Vec2D speed);

    // Check if object is on any of the screen boundaries
    void checkIsOnBoundaries();
    bool isOnTopBoundary();
    bool isOnBottomBoundary();
    bool isOnLeftBoundary();
    bool isOnRightBoundary();

    // Updates object position
    void updatePosition();

    virtual void modifySpeed() = 0;

protected:
    Vec2D m_position;
    Vec2D m_dimensions;

    Vec2D m_speed;

    bool m_isOnTopBound;
    bool m_isOnBottomBound;
    bool m_isOnLeftBound;
    bool m_isOnRightBound;
};

#endif
