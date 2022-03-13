#ifndef PADDLE_H
#define PADDLE_H    

#include "object.hpp"

class Paddle : public Object {
public:
    Paddle() : Object() {};
    ~Paddle(){};

    void checkBoundaries();
    void updatePosition();


private:


};

#endif
