#ifndef GLUT_DISPLAY_H_
#define GLUT_DISPLAY_H_

#include "DisplayInterface.h"

class GlutDisplay : public DisplayInterface {
public: // interfaces
    void SetClearColor(float r, float g, float b, float a);
    void SetWindowName(std::string name);
    void SetWindowSize(int w, int h);
    void SetWindowPosition(int x, int y);
    void Init(int argc, char** argv);
    void Run();
    void RegisterMouseCallback(std::function<void(int, int)> cb);
    void RegisterCursorCallback(std::function<void(int, int)> cb);
    void RegisterKeyboardCallback(std::function<void(int)> cb);
    void RegisterDrawCallback(std::function<void()> cb);
    void RegisterUpdateCallback(std::function<void(double)> cb);

private: // static methods
    static void reshape_func(int w, int h);
    static void visibility_func(int state);
    static void keyboard_func(unsigned char key, int x, int y);
    static void special_func(int key, int x, int y);
    static void motion_func(int x, int y);
    static void mouse_func(int button, int state, int x, int y);
    static void display_func();
    static void idle_func();

public:
    GlutDisplay();
    ~GlutDisplay();

private:
    void Reshape(int w, int h);
    void Visibility(int state);
    void Keyboard(int key, int x, int y);
    void Cursor(int x, int y);
    void MouseButton(int button, int state, int x, int y);
    void Draw();
    void Idle();

private:
    void UpdateViewport();
    void UpdateCursor(int x, int y);

private: // members
    float clear_red_;
    float clear_green_;
    float clear_blue_;
    float clear_alpha_;
    std::string window_name_;
    int window_width_;
    int window_height_;
    int window_left_;
    int window_top_;
    int cursor_x_;
    int cursor_y_;
    std::function<void(int, int)> mouse_callback_;
    std::function<void(int)> keyboard_callback_;
    std::function<void(int, int)> cursor_callback_;
    std::function<void()> draw_callback_;
    std::function<void(double)> update_callback_;
};

#endif  // GLUT_DISPLAY_H_

