#include "engine.hpp"

#include <iostream>
#include <GL/glut.h>
#include <GL/freeglut.h>

Engine::Engine() : m_paddleL(Vec2D(0.02f, 0.32f)), 
                m_paddleR(Vec2D(0.02f, 0.32f)), 
                m_ball(Vec2D(0.025f, 0.04f)) {
}

Engine::~Engine(){
}

/** Inits objects game objects each time the game is restarted (game start and after each scored goal) */
void Engine::initObjects(){
    // Init objects positions
    m_paddleL.setPosition(-0.9f, 0.0f);
    m_paddleR.setPosition(0.9f, 0.0f);
    m_ball.setPosition(0.0f, 0.0f);
    // Init ball speed
    m_ball.setSpeed(Vec2D(SPEED_UNIT, SPEED_UNIT));
    // Init ball tracker
    m_ballTracker.init();
}

/** Returns by reference an object (the object returned depends on the input parameter) */ 
Object& Engine::getObject(ObjectType objectType) {
    if (objectType == ObjectType::PaddleLeft)
        return m_paddleL;
    else if (objectType == ObjectType::PaddleRight)
        return m_paddleR;
    else
        return m_ball;        
}

/** Returns object boundaries */
Boundaries Engine::getObjectBoundaries(ObjectType objectType) {
    Object &obj = getObject(objectType);
    return obj.getBoundaries();
}

/** Returns object boundaries after next movement */
Boundaries Engine::getFutureObjectBoundaries(ObjectType objectType) {
    Object &obj = getObject(objectType);
    return obj.getFutureBoundaries();
}

/** Returns left player score */
int Engine::getLeftScore() {
    return m_paddleL.getScore();
}

/** Returns right player score */
int Engine::getRightScore() {
    return m_paddleR.getScore();
}

/** Sets the speed of the object passed as parameter */
void Engine::setObjectSpeed(ObjectType objectType, Vec2D speed) {
    Object &obj = getObject(objectType);
    obj.setSpeed(speed);
}

/** Does all game mechanics computations to update for next frame */
void Engine::refreshNextFrame() {
    // Checks game events that affect score or object's speed
    checkCollisions();
    bool goalScored = checkGoalAddScore();
    // If a goal has been scored, set all objects positions to the initial ones
    if (goalScored)
        initObjects();
    else {
        // Estimate and update right paddle speed to follow ball
        float speed = m_ballTracker.update(m_ball.getPosition().y, m_paddleR.getPosition().y);
        m_paddleR.setSpeed(Vec2D(0.0f, 10.0f * speed * SPEED_UNIT));
        // Modify objects' speeds accordingly
        modifySpeed();        
        // Update objects' positions 
        updatePositions();
        resetPaddlesSpeed();
    }
}

/** Makes necessary movements so that right paddle follows the ball vertically */
void Engine::followBallPaddleR() {
    Vec2D ballPosition = m_ball.getPosition();
    Boundaries paddleBound = m_paddleR.getBoundaries();
    if (ballPosition.y > paddleBound.b)
        m_paddleR.setSpeed(Vec2D(0.0f, 3.0f * SPEED_UNIT));
    else if (ballPosition.y < paddleBound.t)
        m_paddleR.setSpeed(Vec2D(0.0f, -3.0f * SPEED_UNIT));
}

/** Checks if there are collisions and modifies movement accordingly */
void Engine::checkCollisions() {
    // Check that the objects don't move out of the screen
    m_paddleL.checkIsOnBoundaries();
    m_paddleR.checkIsOnBoundaries();
    m_ball.checkIsOnBoundaries();

    // Check collision between ball and paddles
    Boundaries boubdFutL = getFutureObjectBoundaries(ObjectType::PaddleLeft);
    Boundaries boubdFutR = getFutureObjectBoundaries(ObjectType::PaddleRight);
    m_ball.checkPaddlesCollision(boubdFutL, boubdFutR);
}

/** Check if a goal is scored, in this case add point and reset object positions */
bool Engine::checkGoalAddScore() {
    // Check if goal has been scored
    bool goalLeftPlayer, goalRightPlayer;
    m_ball.checkGoal(goalLeftPlayer, goalRightPlayer);
    // If a goal has been scored, add point to the appropriate player
    if (goalLeftPlayer)
        m_paddleR.addOnePoint();
    if (goalRightPlayer)
        m_paddleL.addOnePoint();
    return goalLeftPlayer || goalRightPlayer;
}

/** Modify movement of the objects according to the computed collisions */
void Engine::modifySpeed() {
    m_paddleL.modifySpeed();
    m_paddleR.modifySpeed();
    m_ball.modifySpeed();
}

/** Updates moving objects position */
void Engine::updatePositions() {
    // Updates positions of the objects
    m_ball.updatePosition();
    m_paddleL.updatePosition();
    m_paddleR.updatePosition();
}

/** Sets the paddles speeds to zero */
void Engine::resetPaddlesSpeed() {
    m_paddleL.setSpeed(Vec2D(0.0f, 0.0f));
    m_paddleR.setSpeed(Vec2D(0.0f, 0.0f));
}