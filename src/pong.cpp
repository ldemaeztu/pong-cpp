#include "engine.h"

#include <GL/glut.h>
#include <GL/freeglut.h>

#include <iostream>

Engine engine;

void keySpecialFunc(int key, int x, int y) {
	switch(key){
		case GLUT_KEY_UP:
            engine.setPaddleLSpeed(1.0f);
			break;
		case GLUT_KEY_DOWN:
			engine.setPaddleLSpeed(-1.0f);
			break;
	}    
}

void keyKeyboardFunc(unsigned char key, int x, int y) {
	switch(key){
        case 'q':
            exit(0);
	}    
}

void drawScore() {
    glColor3f(1.0f, 0.0f, 0.0f); 
    glRasterPos2f(-0.5f, 0.9f);
    std::string text1 = std::to_string(0);
    glutBitmapString(GLUT_BITMAP_TIMES_ROMAN_24, (const unsigned char*)text1.c_str());

    glColor3f(0.0f, 1.0f, 0.0f); 
    glRasterPos2f(0.5f, 0.9f);
    std::string text2 = std::to_string(0);
    glutBitmapString(GLUT_BITMAP_TIMES_ROMAN_24, (const unsigned char*)text2.c_str());
}

void drawPaddle(Position pos, Dimensions dims) {
    glColor3f(1.0f, 1.0f, 1.0f);
    glLineWidth(30);

    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

    glBegin(GL_POLYGON);
        glVertex2f(pos.x - dims.w/2.0f, pos.y - dims.h/2.0f);
        glVertex2f(pos.x + dims.w/2.0f, pos.y - dims.h/2.0f);
        glVertex2f(pos.x + dims.w/2.0f, pos.y + dims.h/2.0f);
        glVertex2f(pos.x - dims.w/2.0f, pos.y + dims.h/2.0f);
    glEnd();

    glFlush();       
}


void renderScene() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    drawScore();
    drawPaddle(engine.getPaddleLPosition(), engine.getPaddleLDimensions());
    drawPaddle(engine.getPaddleRPosition(), engine.getPaddleRDimensions());
    glutSwapBuffers();
    }

void renderTitle(int value) {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glColor3f(1.0f, 1.0f, 1.0f); 
    glRasterPos2f(-0.15f, 0.0f);
    std::string text("Welcome to pong");
    glutBitmapString(GLUT_BITMAP_TIMES_ROMAN_24, (const unsigned char*)text.c_str());
    glutSwapBuffers();
}

void update(int value) {
    engine.updatePositions();

    glutTimerFunc(20, update, value);
    glutPostRedisplay();
}

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
    engine.initObjects();

    initGraphics(argc, argv);
}