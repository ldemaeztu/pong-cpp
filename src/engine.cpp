#include "engine.hpp"

#include <iostream>
#include <GL/glut.h>
#include <GL/freeglut.h>

Engine::Engine(){

}

Engine::~Engine(){

}

void Engine::initObjects(){
    // Init objects positions and dimensions
    m_paddleL.setPosition(-0.9f, 0.0f);
    m_paddleL.setDimensions(0.02f, 0.32f);
    m_paddleR.setPosition(0.9f, 0.0f);
    m_paddleR.setDimensions(0.02f, 0.32f);
    m_ball.setPosition(0.0f, 0.0f);
    m_ball.setDimensions(0.025f, 0.04f);

    setObjectSpeed(ObjectType::Ball, Vector2D(SPEED_UNIT, SPEED_UNIT));    
}

Object& Engine::getObject(ObjectType objectType) {
    if (objectType == ObjectType::PaddleLeft)
        return m_paddleL;
    else if (objectType == ObjectType::PaddleRight)
        return m_paddleR;
    else
        return m_ball;        
}

Vector2D Engine::getObjectPosition(ObjectType objectType) {
    Object &obj = getObject(objectType);
    return obj.getPosition();
}

Dimensions Engine::getObjectDimensions(ObjectType objectType) {
    Object &obj = getObject(objectType);
    return obj.getDimensions();
}

Boundaries Engine::getObjectBoundaries(ObjectType objectType) {
    Object &obj = getObject(objectType);
    return obj.getBoundaries();
}

Boundaries Engine::getFutureObjectBoundaries(ObjectType objectType) {
    Object &obj = getObject(objectType);
    return obj.getBoundaries();
}

void Engine::setObjectSpeed(ObjectType objectType, Vector2D speed) {
    Object &obj = getObject(objectType);
    obj.setSpeed(speed);
}

void Engine::followBall() {
    Vector2D ballPosition = m_ball.getPosition();
    Vector2D paddlePosition = m_paddleR.getPosition();
    if (ballPosition.y > paddlePosition.y)
        m_paddleR.setSpeed(Vector2D(0.0f, 3.0f * SPEED_UNIT));
    else if (ballPosition.y < paddlePosition.y)
        m_paddleR.setSpeed(Vector2D(0.0f, -3.0f * SPEED_UNIT));
}

/** Checks if there are collisions and modifies movement accordingly */
void Engine::checkCollisions() {
    // Check that the objects don't move out of the screen
    m_paddleL.checkBoundaries();
    m_paddleR.checkBoundaries();
    m_ball.checkBoundaries();

    // Check collision between ball and paddle
    Boundaries bFutL = getFutureObjectBoundaries(ObjectType::PaddleLeft);
    m_ball.checkCollision(bFutL);
    Boundaries bFutR = getFutureObjectBoundaries(ObjectType::PaddleRight);
    m_ball.checkCollision(bFutR);
}

/** Updates moving objects position */
void Engine::updatePositions() {
    m_ball.updatePosition();
    m_paddleL.updatePosition();
    m_paddleR.updatePosition();
}

