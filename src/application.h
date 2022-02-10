#ifndef APPLICATION_H
#define APPLICATION_H    

class Application {
public:
    Application();
    ~Application();

    // Does GLUT initialization and launch main GLUT loop
    static void launchApp(int argc, char* argv[]);
    // Renders the complete scene on the screen
    static void renderScene();
    // Renders the initial title
    static void renderTitle(int value);
    // Draws the score
    static void drawScore();
    // Updates the status of the system
    static void update(int value);
    // Methods to capture input
    static void keyFunc(int key, int x, int y);        
    static void quitFunc(unsigned char key, int x, int y);
};

#endif
