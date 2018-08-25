#ifndef GLUT_DISPLAY_H_
#define GLUT_DISPLAY_H_

#include "DisplayCommon.h"

class GlutDisplay : public DisplayCommon {

private: // static methods
    static void reshape_func(int w, int h);
    static void visibility_func(int state);
    static void keyboard_func(unsigned char key, int x, int y);
    static void keyboard_up_func(unsigned char key, int x, int y);
    static void special_func(int key, int x, int y);
    static void special_up_func(int key, int x, int y);
    static void motion_func(int x, int y);
    static void mouse_func(int button, int state, int x, int y);
    static void display_func();
    static void idle_func();

public:
    GlutDisplay();
    ~GlutDisplay();
    void Init(int argc, char ** argv);
    void Run();

private:
    void Reshape(int w, int h);
    void Visibility(int state);
    void Keyboard(int key, bool pressed, bool special, int x, int y);
    void Cursor(int x, int y);
    void MouseButton(int button, int state, int x, int y);
    void Draw();
    void Idle();

private:
    void UpdateViewport();
    void UpdateCursor(int x, int y);
};

#endif  // GLUT_DISPLAY_H_
