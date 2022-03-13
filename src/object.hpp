#ifndef OBJECT_H
#define OBJECT_H    

struct Dimensions
{
    float w;
    float h;
};


struct Boundaries
{
    Boundaries(float l_, float r_, float t_, float b_) : l(l_), r(r_), t(t_), b(b_) {};
    float l; // Left
    float r; // Right
    float t; // Top
    float b; // Bottom
};


struct Vector2D
{
    Vector2D(float cx, float cy) : x(cx), y(cy) {};
    float x;
    float y;
};

class Object {
public:
    Object();
    ~Object();

    void setPosition(float x, float y);
    void setDimensions(float w, float h);

    Vector2D getPosition();
    Dimensions getDimensions();

    void setSpeed(Vector2D speed);

    virtual void updatePosition() = 0;

    // Los distintos tipos de objetos implementan el chequeo de bordes de manera diferente
    virtual void checkBoundaries() = 0;

    float getLeftBoundary();
    float getRightBoundary();
    float getTopBoundary();
    float getBottomBoundary();

protected:
    Vector2D m_position;
    Dimensions m_dimensions;

    Vector2D m_speed;
};

#endif
