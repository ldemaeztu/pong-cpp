#ifndef ENGINE_H
#define ENGINE_H    

#include "paddle.h"

class Engine {
public:
    Engine();
    ~Engine();

    // Inits objects
    void initObjects();

    Position getPaddleLPosition();
    Position getPaddleRPosition();
    Dimensions getPaddleLDimensions();
    Dimensions getPaddleRDimensions();

    void setPaddleLSpeed(float speed);
    void setPaddleRSpeed(float speed);

    void updatePositions();

private:
    Paddle m_paddleL;
    Paddle m_paddleR;

};

#endif
