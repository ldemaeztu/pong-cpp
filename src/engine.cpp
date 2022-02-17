#include "engine.h"

#include <iostream>
#include <GL/glut.h>
#include <GL/freeglut.h>

Engine::Engine(){

}

Engine::~Engine(){

}

void Engine::initObjects(){
    m_paddleL.setPosition(-0.9f, 0.0f);
    m_paddleL.setDimensions(0.01f, 0.2f);

    m_paddleR.setPosition(0.9f, 0.0f);
    m_paddleR.setDimensions(0.01f, 0.2f);
}

Position Engine::getPaddleLPosition() {
    return m_paddleL.getPosition();
}

Position Engine::getPaddleRPosition() {
    return m_paddleR.getPosition();
}

Dimensions Engine::getPaddleLDimensions() {
    return m_paddleL.getDimensions();
}

Dimensions Engine::getPaddleRDimensions() {
    return m_paddleR.getDimensions();
}

void Engine::setPaddleLSpeed(float speed) {
    m_paddleL.setSpeed(speed);
}

void Engine::setPaddleRSpeed(float speed) {
    m_paddleR.setSpeed(speed);
}

void Engine::updatePositions() {
    m_paddleL.updatePosition();
    m_paddleR.updatePosition();
}

