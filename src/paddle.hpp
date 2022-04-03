#ifndef PADDLE_H
#define PADDLE_H    

#include "object.hpp"

class Paddle : public Object {
public:
    Paddle();
    ~Paddle();

    void modifyMovement();
    void updatePosition();

    int getScore();
    void addOnePoint();

private:
    int m_score;

};

#endif
