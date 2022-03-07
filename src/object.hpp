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

struct Speed
{
    Speed(float vx, float vy) : x(vx), y(vy) {};
    float x;
    float y;
};

class Object {
public:
    Object(bool continuousSpeed);
    ~Object();

    void setPosition(float x, float y);
    void setDimensions(float w, float h);

    Position getPosition();
    Dimensions getDimensions();

    void setSpeed(Speed speed);

    void updatePosition();
    void forceYPosition(float y);

private:
    Position m_position;
    Dimensions m_dimensions;

    Speed m_speed;
    bool m_continuousMovement;
};

#endif
