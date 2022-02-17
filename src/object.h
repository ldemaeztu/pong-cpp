#ifndef OBJECT_H
#define OBJECT_H    

struct Position
{
    float x;
    float y;
};

struct Dimensions
{
    float w;
    float h;
};


class Object {
public:
    Object();
    ~Object();

    void setPosition(float x, float y);
    void setDimensions(float w, float h);

    Position getPosition();
    Dimensions getDimensions();

    void setSpeed(float speed);

    void updatePosition();

private:
    Position m_position;
    Dimensions m_dimensions;

    float m_speed;
};

#endif
