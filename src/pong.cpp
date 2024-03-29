#include "configloader.hpp"

#include <iostream>

#include <GL/glut.h>
#include <GL/freeglut.h>

#include "engine.hpp"

std::unique_ptr<Engine> engine; // Engine that control the game dynamics

/** Updates the speed of the player's paddle if a key is pressed */
void keySpecialFunc(const int key, const int x, const int y) {
	switch(key){
		case GLUT_KEY_UP:
            engine->setPlayerPaddleDirection(1);
			break;
		case GLUT_KEY_DOWN:
			engine->setPlayerPaddleDirection(0);
			break;
	}    
}

/** Quits if 'q' key is pressed */
void keyKeyboardFunc(const unsigned char key, const int x, const int y) {
	switch(key){
        case 'q':
        case 'Q':
            exit(0);
	}    
}
/** Draws game scores */
void drawScores() {
    // Draws score left player
    glColor3f(1.0f, 0.0f, 0.0f); 
    glRasterPos2f(-0.5f, 0.9f);
    std::string text1 = std::to_string(engine->getPlayerScore(ObjectType::PaddleLeft));
    glutBitmapString(GLUT_BITMAP_TIMES_ROMAN_24, (const unsigned char*)text1.c_str());
    // Draws score right player
    glColor3f(0.0f, 1.0f, 0.0f); 
    glRasterPos2f(0.5f, 0.9f);
    std::string text2 = std::to_string(engine->getPlayerScore(ObjectType::PaddleRight));
    glutBitmapString(GLUT_BITMAP_TIMES_ROMAN_24, (const unsigned char*)text2.c_str());
}

/** Draws rectangle given boundaries */
void drawRectangle(const Boundaries boundaries) {
    glColor3f(1.0f, 1.0f, 1.0f);
    glLineWidth(30);

    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

    glBegin(GL_POLYGON);
        glVertex2f(boundaries.l, boundaries.t);
        glVertex2f(boundaries.r, boundaries.t);
        glVertex2f(boundaries.r, boundaries.b);
        glVertex2f(boundaries.l, boundaries.b);
    glEnd();

    glFlush();       
}

/** Renders a frame */
void renderScene() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    drawScores();
    drawRectangle(engine->getObjectBoundaries(ObjectType::PaddleLeft));
    drawRectangle(engine->getObjectBoundaries(ObjectType::PaddleRight));
    drawRectangle(engine->getObjectBoundaries(ObjectType::Ball));
    glutSwapBuffers();
}

/** Renders game title */
void renderTitle(const int value) {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glColor3f(1.0f, 1.0f, 1.0f); 
    glRasterPos2f(-0.15f, 0.0f);
    std::string text("Welcome to pong");
    glutBitmapString(GLUT_BITMAP_TIMES_ROMAN_24, (const unsigned char*)text.c_str());
    glutSwapBuffers();
}

/** Called one time per frame */
void update(const int value) {
    engine->refreshNextFrame();

    glutTimerFunc(20, update, value);
    glutPostRedisplay();
}

/** Inits graphics and configures periodic refreshing */
void initGraphics(int argc, char* argv[]){
    glutInit(&argc, argv);

    glutSetOption(GLUT_ACTION_ON_WINDOW_CLOSE, GLUT_ACTION_CONTINUE_EXECUTION);
    glutInitWindowPosition(200, 0);
    glutInitWindowSize(1200,800);
    glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);
    glutCreateWindow("Pong");

    //set callback
    glutDisplayFunc(renderScene);

    glutSpecialFunc(keySpecialFunc);
    glutKeyboardFunc(keyKeyboardFunc);
    glutTimerFunc(2000, update, 0);
    glutTimerFunc(10, renderTitle, 0);

    // enter GLUT event processing cycle
    glutMainLoop();
}

int main(int argc, char* argv[]) {
    std::unique_ptr<ConfigLoader> config = std::make_unique<ConfigLoader>("config/pong.conf");
    engine = std::make_unique<Engine>(config.get());
    engine->initObjects();
    initGraphics(argc, argv);
}