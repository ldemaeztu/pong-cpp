#ifndef OBJECT_H
#define OBJECT_H    

#include <algorithm>
#include <limits>

#define SCREEN_LIMIT 0.99f

struct Boundaries {
    Boundaries(const float l_, const float r_, const float t_, const float b_) : l(l_), r(r_), t(t_), b(b_) {};
    float area() {return std::max(0.0f, r - l) * std::max(0.0f, b - t);}
    float l; // Left
    float r; // Right
    float t; // Top
    float b; // Bottom
};


struct Vec2D {
    Vec2D() : x(std::numeric_limits<float>::quiet_NaN()), y(std::numeric_limits<float>::quiet_NaN()) {};
    Vec2D(const float x_, const float y_) : x(x_), y(y_) {};
    float x;
    float y;

    Vec2D operator+(Vec2D v)
    {
        return Vec2D(x + v.x, y + v.y);
    }

    Vec2D operator-(Vec2D v)
    {
        return Vec2D(x - v.x, y - v.y);
    }
};

struct Segment
{
    Segment() {};
    Segment(const Vec2D p1_, const Vec2D p2_) : p1(p1_), p2(p2_) {};
    Vec2D p1;
    Vec2D p2;
};

enum class ObjectType {
  PaddleLeft,
  PaddleRight,
  Ball
};

class Object {
public:
    Object();
    Object(Vec2D dim);
    ~Object();

    // Get object properties
    Vec2D getPosition();
    Vec2D getSpeed();
    Boundaries getBoundaries();
    void getSegments(Segment& leftSegment, Segment& rightSegment, Segment& topSegment, Segment& bottomSegment);

    // Set object properties
    void setDimensions(const float w, const float h);
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

    virtual void updateSpeed() = 0;

private:
    float getLeftBoundary();
    float getRightBoundary();
    float getTopBoundary();
    float getBottomBoundary();

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
