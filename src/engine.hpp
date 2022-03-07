#ifndef ENGINE_H
#define ENGINE_H    

#include "ball.hpp"
#include "paddle.hpp"

#define SPEED_UNIT 0.01f

enum class ObjectType {
  PaddleLeft,
  PaddleRight,
  Ball
};

class Engine {
public:
    Engine();
    ~Engine();

    // Inits objects
    void initObjects();

    Object& getObject(ObjectType objectType);

    Position getObjectPosition(ObjectType objectType);
    Dimensions getObjectDimensions(ObjectType objectType);

    void setObjectSpeed(ObjectType objectType, Speed speed);

    void updatePositions();

private:
    Paddle m_paddleL;
    Paddle m_paddleR;

    Ball m_ball;

};

#endif
