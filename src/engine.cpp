#include "engine.hpp"

#include <iostream>
#include <numbers> 

#include <GL/glut.h>
#include <GL/freeglut.h>

#include "geometry.hpp"


Engine::Engine(ConfigLoader* configManager) : 
                m_config(configManager),
                m_paddleL(Vec2D(configManager->get<float>("pL", "w"), configManager->get<float>("pL", "h"))),
                m_paddleR(Vec2D(configManager->get<float>("pR", "w"), configManager->get<float>("pR", "h"))),
                m_ball(configManager, Vec2D(configManager->get<float>("b", "w"), configManager->get<float>("b", "h"))),
                m_ballTracker(configManager) {
}

Engine::~Engine() {
}

/** Inits objects game objects each time the game is restarted (game start and after each scored goal) */
void Engine::initObjects() {
    // Init objects positions
    m_paddleL.setPosition(m_config->get<float>("pL", "x"), m_config->get<float>("pL", "y"));
    m_paddleR.setPosition(m_config->get<float>("pR", "x"), m_config->get<float>("pR", "y"));
    m_ball.setPosition(m_config->get<float>("b", "x"), m_config->get<float>("b", "y"));
    // Init ball speed
    m_ball.setSpeed(Vec2D(m_config->get<float>("g", "speed_unit") * cos(M_PI/4), m_config->get<float>("g", "speed_unit") * sin(M_PI/4)));
    // Init ball tracker
    m_ballTracker.init();
}

/** Returns by reference an object (the object returned depends on the input parameter) */ 
Object& Engine::getObject(ObjectType objectType) {
    assert(
        objectType == ObjectType::PaddleLeft 
        || objectType == ObjectType::PaddleRight 
        || objectType == ObjectType::Ball
    );
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
    assert(objectType == ObjectType::PaddleLeft || objectType == ObjectType::PaddleRight);
    return objectType == ObjectType::PaddleLeft ? m_paddleL.getScore() : m_paddleR.getScore();
}

/** Sets the direction of the object passed as parameter (0: down, 1: up) */
void Engine::setObjectDirection(ObjectType objectType, bool direction) {
    Object &obj = getObject(objectType);
    float speed_multiplier = m_config->get<float>("pR", "speed_multiplier");
    float speed_unit = m_config->get<float>("g", "speed_unit");
    float direction_modifier = direction ? 1.0f : -1.0f; 
    Vec2D speed = Vec2D(0.0f, direction_modifier * speed_multiplier * speed_unit);
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
        float speed_estimation = m_ballTracker.update(m_ball.getPosition().y, m_paddleR.getPosition().y);
        float speed_unit = m_config->get<float>("g", "speed_unit");
        m_paddleR.setSpeed(Vec2D(0.0f, speed_estimation * speed_unit));
        // Modify objects' speeds
        updateSpeed();        
        // Update objects' positions 
        updatePositions();
        resetPaddlesSpeed();
    }
}

/** Checks if there are collisions and modifies movement accordingly */
void Engine::checkCollisions() {
    // Check that the objects don't move out of the screen
    m_paddleL.checkIsOnBoundaries();
    m_paddleR.checkIsOnBoundaries();
    m_ball.checkIsOnBoundaries();

    // Check collision between ball and paddles (only with the paddle in this half of the screen)
    if (m_ball.getPosition().x < 0.0f)
        checkBallPaddleCollision(ObjectType::PaddleLeft);
    else
        checkBallPaddleCollision(ObjectType::PaddleRight);
}

/** Checks if there is a collision between the ball and a paddle */
void Engine::checkBallPaddleCollision(ObjectType objectType) {
    Paddle paddle = objectType == ObjectType::PaddleLeft ? m_paddleL : m_paddleR;
    Vec2D ballPosition = m_ball.getPosition();
    Vec2D ballSpeed = m_ball.getSpeed();
    Vec2D paddleSpeed = paddle.getSpeed();

    // Compute a line from the initial ball position to the final ball position minus the paddle movement
    Vec2D ballInitialPoint = ballPosition;
    Vec2D ballFinalPoint = ballPosition + ballSpeed - paddleSpeed;
    Segment ballSegment(ballInitialPoint, ballFinalPoint);

    // Get paddle segments
    Segment paddleLeftSegment, paddleRightSegment, paddleTopSegment, paddleBottomSegment;
    paddle.getSegments(paddleLeftSegment, paddleRightSegment, paddleTopSegment, paddleBottomSegment);
    Segment paddleSideSegment = objectType == ObjectType::PaddleLeft ? paddleRightSegment : paddleLeftSegment;

    // Intersect this line with the boundaries of the paddle to check if there is a collision
    Vec2D intersectionSide = Geometry::computeSegmentsIntersection(ballSegment, paddleSideSegment);
    Vec2D intersectionTop = Geometry::computeSegmentsIntersection(ballSegment, paddleTopSegment);
    Vec2D intersectionBottom = Geometry::computeSegmentsIntersection(ballSegment, paddleBottomSegment);

    // Decide if there has been a collision with the side of the paddle (horizontal collision)    
    // or with the top or bottom of the paddle (vertical collision)
    bool horizontalCollision = !std::isnan(intersectionSide.x); 
    bool verticalCollision = (!std::isnan(intersectionTop.x) && ballSpeed.y > 0) || 
        (!std::isnan(intersectionBottom.x) && ballSpeed.y < 0); 

    // If there is an horizontal collision, compute the rebound angle
    float angle = 0.0f;
    if (horizontalCollision)
        angle = computeReboundAngle(paddleSideSegment, intersectionSide, objectType == ObjectType::PaddleRight);

    // Update collision information
    m_ball.updateCollision(horizontalCollision, verticalCollision, angle);
}

/** Computes the rebound angle after an horizontal paddle-ball collision */
float Engine::computeReboundAngle(Segment paddleSegment, Vec2D intersectionPoint, bool isRightPaddle) {
    // Compute the relative position of the intersection point inside the paddle segment
    float middlePointY = (paddleSegment.p1.y + paddleSegment.p2.y) / 2.0;
    float length = abs(paddleSegment.p1.y - paddleSegment.p2.y) / 2.0;
    float horizontalCollisionPosition = (intersectionPoint.y - middlePointY) / length;

    // Transform collision position to rebound angle
    float angle = horizontalCollisionPosition * std::numbers::pi / m_config->get<float>("g", "angle_divisor");

    // If it was the right paddle, adapt the rebound angle
    if (isRightPaddle)
        angle = angle >= 0.0 ? std::numbers::pi - angle : -std::numbers::pi - angle;
    
    return angle;
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
void Engine::updateSpeed() {
    m_paddleL.updateSpeed();
    m_paddleR.updateSpeed();
    m_ball.updateSpeed();
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