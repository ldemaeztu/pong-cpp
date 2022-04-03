#ifndef OBJECT_H
#define OBJECT_H    

#include <algorithm>

#define SCREEN_LIMIT 0.99f

struct Dimensions
{
    float w;
    float h;
};


struct Boundaries
{
    Boundaries(const float l_, const float r_, const float t_, const float b_) : l(l_), r(r_), t(t_), b(b_) {};
    float area() {return std::max(0.0f, r - l) * std::max(0.0f, b - t);}
    float l; // Left
    float r; // Right
    float t; // Top
    float b; // Bottom
};


struct Vector2D
{
    Vector2D(const float x_, const float y_) : x(x_), y(y_) {};
    float x;
    float y;
};

class Object {
public:
    Object();
    ~Object();

    void setPosition(const float x, const float y);
    void setDimensions(const float w, const float h);

    Vector2D getPosition();
    Dimensions getDimensions();

    void setSpeed(const Vector2D speed);

    virtual void modifyMovement() = 0;
    virtual void updatePosition() = 0;

    void checkIsOnBoundaries();
    bool isOnTopBoundary();
    bool isOnBottomBoundary();
    bool isOnLeftBoundary();
    bool isOnRightBoundary();

    float getLeftBoundary();
    float getRightBoundary();
    float getTopBoundary();
    float getBottomBoundary();

    Boundaries getBoundaries();
    Boundaries getFutureBoundaries();

protected:
    Vector2D m_position;
    Dimensions m_dimensions;

    Vector2D m_speed;

    bool m_isOnTopBound;
    bool m_isOnBottomBound;
    bool m_isOnLeftBound;
    bool m_isOnRightBound;

};

#endif
