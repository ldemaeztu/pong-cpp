#include "application.h"

#include <iostream>
#include <GL/glut.h>
#include <GL/freeglut.h>

Application::Application(){

}

Application::~Application(){

}

void Application::launchApp(int argc, char* argv[]){
    glutInit(&argc, argv);

    glutSetOption(GLUT_ACTION_ON_WINDOW_CLOSE, GLUT_ACTION_CONTINUE_EXECUTION);
    glutInitWindowPosition(200, 0);
    glutInitWindowSize(1200,800);
    glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);
    glutCreateWindow("Pong");

    //set callback
    glutKeyboardFunc(quitFunc);
    glutDisplayFunc(renderScene);

    glutSpecialFunc(keyFunc);
    glutTimerFunc(2000, update, 0);
    glutTimerFunc(10, renderTitle, 0);

    // enter GLUT event processing cycle
    glutMainLoop();

    std::cout << "Welcome to Pong!" << std::endl;
}

void Application::renderScene() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    drawScore();
    glutSwapBuffers();
    }

void Application::renderTitle(int value) {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glColor3f(1.0f, 0.0f, 0.0f); 
    glRasterPos2f(-0.15f, 0.0f);
    std::string text("Welcome to pong");
    glutBitmapString(GLUT_BITMAP_TIMES_ROMAN_24, (const unsigned char*)text.c_str());
    glutSwapBuffers();
}

void Application::drawScore() {
    glColor3f(1.0f, 0.0f, 0.0f); 
    glRasterPos2f(-0.5f, 0.9f);
    std::string text1 = std::to_string(0);
    glutBitmapString(GLUT_BITMAP_TIMES_ROMAN_24, (const unsigned char*)text1.c_str());

    glColor3f(0.0f, 1.0f, 0.0f); 
    glRasterPos2f(0.5f, 0.9f);
    std::string text2 = std::to_string(0);
    glutBitmapString(GLUT_BITMAP_TIMES_ROMAN_24, (const unsigned char*)text2.c_str());
}

void Application::update(int value) {
    glutTimerFunc(20, update, value);
    glutPostRedisplay();
}

void Application::keyFunc(int key, int x, int y) {
}

void Application::quitFunc(unsigned char key, int x, int y) {
    if(key == 'q')
        exit(0);
}