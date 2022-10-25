#ifndef ENGINE_H
#define ENGINE_H    

#include "ball.hpp"
#include "paddle.hpp"
#include "kalman.hpp"
#include "balltracker.hpp"

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

    // Get game score
    int getPlayerScore(const ObjectType objectType);

    // Set object properties
    void setObjectSpeed(const ObjectType objectType, const Vec2D speed);

    // AI-controlled paddle movement computation
    void initKalman();
    void updateKalman(float ballY);

    // Game mechanics 
    void refreshNextFrame();
    void followBallPaddleR();
    void checkCollisions();
    bool checkGoalAddScore();
    void updateSpeed();
    void updatePositions();
    void resetPaddlesSpeed();
    float computeReboundAngle(Segment paddleSegment, Vec2D intersectionPoint, bool isRightPaddle);

    void checkBallPaddleCollision(ObjectType objectType);

private:
    // Game objects
    Paddle m_paddleL;
    Paddle m_paddleR;
    Ball m_ball;
    BallTracker m_ballTracker;
};

#endif
