#ifndef PADDLE_H
#define PADDLE_H    

#include "object.hpp"

class Paddle : public Object {
public:
    Paddle(ConfigLoader *config, Vec2D dim);
    ~Paddle();

    int getScore();
    void addOnePoint();

    void updatePosition();
    void modifySpeed();

private:
    int m_score;
};

#endif
