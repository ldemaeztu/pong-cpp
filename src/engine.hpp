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

    Object& getObject(const ObjectType objectType);

    Vector2D getObjectPosition(const ObjectType objectType);
    Dimensions getObjectDimensions(const ObjectType objectType);
    Boundaries getObjectBoundaries(const ObjectType objectType);
    Boundaries getFutureObjectBoundaries(const ObjectType objectType);

    void setObjectSpeed(const ObjectType objectType, const Vector2D speed);

    void followBall();
    void checkCollisions();
    void updatePositions();

private:
    Paddle m_paddleL;
    Paddle m_paddleR;

    Ball m_ball;

};

#endif
