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

    // Inits all objects in the screen
    void initObjects();

    // Get one of the game objects
    Object& getObject(const ObjectType objectType);

    // Get object properties
    Boundaries getObjectBoundaries(const ObjectType objectType);
    Boundaries getFutureObjectBoundaries(const ObjectType objectType);

    // Get game score
    int getLeftScore();
    int getRightScore();

    // Set object properties
    void setObjectSpeed(const ObjectType objectType, const Vec2D speed);

    // Game mechanics 
    void refreshNextFrame();
    void followBallPaddleR();
    void checkCollisions();
    bool checkGoalAddScore();
    void modifySpeed();
    void updatePositions();
    void resetPaddlesSpeed();

private:
    // Game objects
    Paddle m_paddleL;
    Paddle m_paddleR;
    Ball m_ball;
};

#endif
