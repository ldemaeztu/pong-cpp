#include "engine.hpp"

#include <iostream>
#include <numbers> 

#include <GL/glut.h>
#include <GL/freeglut.h>

#include "geometry.hpp"

Engine::Engine(ConfigLoader* config) :
    m_config(config),
    m_paddleL(config, getPaddleLDims(config)),
    m_paddleR(config, getPaddleRDims(config)),
    m_ball(config, getBallDims(config)),
    m_ballTracker(config) {
}

Engine::~Engine() {
}

/** Returns left paddle dimensions */
Vec2D Engine::getPaddleLDims(ConfigLoader* config) {
    float w = config->get<float>("pL", "w");
    float h = config->get<float>("pL", "h");
    return Vec2D(w, h);
}

/** Returns right paddle dimensions */
Vec2D Engine::getPaddleRDims(ConfigLoader* config) {
    float w = config->get<float>("pR", "w");
    float h = config->get<float>("pR", "h");
    return Vec2D(w, h);
}

/** Returns ball dimensions */
Vec2D Engine::getBallDims(ConfigLoader* config) {
    float w = config->get<float>("b", "w");
    float h = config->get<float>("b", "h");
    return Vec2D(w, h);
}

/** Inits objects game objects each time the game is restarted (start and goals) */
void Engine::initObjects() {
    // Init paddles and ball positions
    float xL = m_config->get<float>("pL", "x");
    float yL = m_config->get<float>("pL", "y");
    m_paddleL.setPosition(xL, yL);
    float xR = m_config->get<float>("pR", "x");
    float yR = m_config->get<float>("pR", "y");
    m_paddleR.setPosition(xR, yR);
    float xB = m_config->get<float>("b", "x");
    float yB = m_config->get<float>("b", "y");
    m_ball.setPosition(xB, yB);
    // Init ball speed
    float speedUnit = m_config->get<float>("g", "speed_unit");
    m_ball.setSpeed(Vec2D(speedUnit * cos(M_PI/4), speedUnit * sin(M_PI/4)));
    // Init ball tracker
    m_ballTracker.init();
}

/** Returns by reference an object (the object returned depends on the input parameter) */ 
Object& Engine::getObject(ObjectType objectType) {
    assert(
        objectType == ObjectType::PaddleLeft 
        || objectType == ObjectType::PaddleRight 
        || objectType == ObjectType::Ball);

    Object *obj;
    if (objectType == ObjectType::PaddleLeft)
        obj = &m_paddleL;
    else if (objectType == ObjectType::PaddleRight)
        obj = &m_paddleR;
    else if (objectType == ObjectType::Ball)
        obj = &m_ball;  
    return *obj;      
}

/** Returns object boundaries */
Boundaries Engine::getObjectBoundaries(ObjectType objectType) {
    Object &obj = getObject(objectType);
    return obj.getBoundaries();
}

/** Returns left or right player score */
int Engine::getPlayerScore(const ObjectType objectType) {
    assert(objectType == ObjectType::PaddleLeft || 
           objectType == ObjectType::PaddleRight);

    return objectType == ObjectType::PaddleLeft ? 
                         m_paddleL.getScore() : m_paddleR.getScore();
}

/** Sets the direction of the player's paddle (0: down, 1: up) */
void Engine::setPlayerPaddleDirection(bool direction) {
    // Compute and set speed
    float speed_multiplier = m_config->get<float>("pL", "speed_multiplier");
    float speed_unit = m_config->get<float>("g", "speed_unit");
    float direction_modifier = direction ? 1.0f : -1.0f; 
    Vec2D speed = Vec2D(0.0f, direction_modifier * speed_multiplier * speed_unit);
    m_paddleL.setSpeed(speed);
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
        float speed_estimation = 
            m_ballTracker.update(m_ball.getPosition().y, m_paddleR.getPosition().y);
        float speed_unit = m_config->get<float>("g", "speed_unit");
        m_paddleR.setSpeed(Vec2D(0.0f, speed_estimation * speed_unit));

        // Modify objects' speeds and positions
        modifyObjectsSpeeds();        
        updatePositions();
    }
}

/** Checks if there are collisions and modifies movement accordingly */
void Engine::checkCollisions() {
    // Check that the objects don't move out of the screen
    m_paddleL.checkIsOnBoundaries();
    m_paddleR.checkIsOnBoundaries();
    m_ball.checkIsOnBoundaries();

    // Check collision between ball and paddles
    Segment l, r, t, b;
    if (m_ball.isOnLeftHalf()) {
        m_paddleL.getSegments(l, r, t, b);
        m_ball.checkBallPaddleCollision(m_paddleL.getSpeed(), r, t, b);
    }
    else {
        m_paddleR.getSegments(l, r, t, b);
        m_ball.checkBallPaddleCollision(m_paddleR.getSpeed(), l, t, b);
    }
}

/** Checks if a goal is scored, in this case add point and reset object positions */
bool Engine::checkGoalAddScore() {
    // Check if goal has been scored
    bool goalLeftPlayer, goalRightPlayer;
    m_ball.checkGoal(goalLeftPlayer, goalRightPlayer);
    // If a goal has been scored, add point to the appropriate player
    if (goalLeftPlayer)
        m_paddleR.addOnePoint();
    else if (goalRightPlayer)
        m_paddleL.addOnePoint();
    return goalLeftPlayer || goalRightPlayer;
}

/** Modifies movement of the objects according to the computed collisions */
void Engine::modifyObjectsSpeeds() {
    m_paddleL.modifySpeed();
    m_paddleR.modifySpeed();
    m_ball.modifySpeed();
}

/** Updates moving objects position */
void Engine::updatePositions() {
    m_ball.updatePosition();
    m_paddleL.updatePosition();
    m_paddleR.updatePosition();
}