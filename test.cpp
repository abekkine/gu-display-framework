#include "DisplayFactory.h"

#include <GL/glut.h>

#include <functional>

bool key_callback(int key, bool pressed, bool special) {
    (void)pressed;
    (void)special;
    switch(key) {
    case 27:
    case 'q':
        exit(0); break;
    default:
        break;
    }

    return true;
}

bool draw_callback() {
    glLoadIdentity();
    glTranslated(400.0, 400.0, 0.0);
    glBegin(GL_QUADS);
    glColor3f(1.0, 0.0, 0.0);
    glVertex2d(0.0, 0.0);
    glColor3f(0.0, 1.0, 0.0);
    glVertex2d(50.0, 0.0);
    glColor3f(0.0, 0.0, 1.0);
    glVertex2d(50.0, 50.0);
    glColor3f(1.0, 0.0, 1.0);
    glVertex2d(0.0, 50.0);
    glEnd();

    return true;
}

int main(int argc, char** argv) {

    DisplayInterface* display = DisplayFactory::getGlutDisplay();

    display->SetWindowName("test");
    display->SetWindowSize(800, 800);
    display->SetWindowPosition(100, 100);
    display->SetClearColor(0.0, 0.0, 0.0, 1.0);

    {
        using namespace std::placeholders;
        display->AddKeyboardHandler( std::bind(key_callback, _1, _2, _3) );
        display->AddRenderer( draw_callback );
    }

    display->Init(argc, argv);

    display->Run();

    return 0;
}
