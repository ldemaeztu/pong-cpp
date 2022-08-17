#ifndef PADDLE_H
#define PADDLE_H    

#include "object.hpp"

class Paddle : public Object {
public:
    Paddle(Vec2D dim);
    ~Paddle();

    int getScore();
    void addOnePoint();

    void updateSpeed();

private:
    int m_score;
};

#endif
