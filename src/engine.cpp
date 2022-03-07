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
    m_paddleL.setDimensions(0.02f, 0.3f);
    m_paddleR.setPosition(0.9f, 0.0f);
    m_paddleR.setDimensions(0.02f, 0.3f);
    m_ball.setPosition(0.0f, 0.0f);
    m_ball.setDimensions(0.025f, 0.04f);

    setObjectSpeed(ObjectType::Ball, Speed(SPEED_UNIT, SPEED_UNIT));    
}
Object& Engine::getObject(ObjectType objectType) {
    if (objectType == ObjectType::PaddleLeft)
        return m_paddleL;
    else if (objectType == ObjectType::PaddleRight)
        return m_paddleR;
    else
        return m_ball;        
}

Position Engine::getObjectPosition(ObjectType objectType) {
    Object &obj = getObject(objectType);
    return obj.getPosition();
}

Dimensions Engine::getObjectDimensions(ObjectType objectType) {
    Object &obj = getObject(objectType);
    return obj.getDimensions();
}

void Engine::setObjectSpeed(ObjectType objectType, Speed speed) {
    Object &obj = getObject(objectType);
    obj.setSpeed(speed);
}

void Engine::updatePositions() {
    // Actualizamos la posición de la bola
    m_ball.updatePosition();

    // Actualizamos la posición de la raqueta del jugador
    m_paddleL.updatePosition();

    // Actualizamos la posición de la raqueta de la IA
    Position ballPosition = m_ball.getPosition();
    m_paddleR.forceYPosition(ballPosition.y);    
}

