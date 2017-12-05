#include "GlutDisplay.h"

#include <GL/glut.h>

static GlutDisplay* display_instance_ = 0;

// Static methods first
void GlutDisplay::reshape_func(int w, int h) {

    display_instance_->Reshape(w, h);
}

void GlutDisplay::visibility_func(int state) {

    display_instance_->Visibility(state);
}

void GlutDisplay::keyboard_func(unsigned char key, int x, int y) {

    display_instance_->Keyboard((int)key, x, y);
}

void GlutDisplay::special_func(int key, int x, int y) {

    display_instance_->Keyboard(key, x, y);
}

void GlutDisplay::motion_func(int x, int y) {

    display_instance_->Cursor(x, y);
}

void GlutDisplay::mouse_func(int button, int state, int x, int y) {

    display_instance_->MouseButton(button, state, x, y);
}

void GlutDisplay::display_func() {

    display_instance_->Draw();
}

void GlutDisplay::idle_func() {

    display_instance_->Idle();
}

// C'TOR & D'TOR
GlutDisplay::GlutDisplay() {
}

GlutDisplay::~GlutDisplay() {
}

// Interface methods
void GlutDisplay::SetClearColor(float r, float g, float b, float a) {

    clear_red_ = r;
    clear_green_ = g;
    clear_blue_ = b;
    clear_alpha_ = a;
}

void GlutDisplay::SetWindowName(std::string name) {

    window_name_ = name;
}

void GlutDisplay::SetWindowSize(int w, int h) {

    window_width_ = w;
    window_height_ = h;
}

void GlutDisplay::SetWindowPosition(int x, int y) {

    window_left_ = x;
    window_top_ = y;
}

void GlutDisplay::Init(int argc, char** argv) {

    if (display_instance_ == 0) {
        display_instance_ = this;
    }

    glutInit(&argc, argv);

    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize(window_width_, window_height_);
    glutInitWindowPosition(window_left_, window_top_);
    glutCreateWindow(window_name_.c_str());

    glutReshapeFunc(reshape_func);
    glutVisibilityFunc(visibility_func);
    glutKeyboardFunc(keyboard_func);
    glutSpecialFunc(special_func);
    glutDisplayFunc(display_func);
    glutMotionFunc(motion_func);
    glutPassiveMotionFunc(motion_func);
    glutIdleFunc(idle_func);
    glutMouseFunc(mouse_func);

    glClearColor(clear_red_, clear_green_, clear_blue_, clear_alpha_);
}

void GlutDisplay::Run() {

    glutMainLoop();
}

void GlutDisplay::RegisterMouseCallback(std::function<void(int, int)> cb) {

    mouse_callback_ = cb;
}

void GlutDisplay::RegisterKeyboardCallback(std::function<void(int)> cb) {

    keyboard_callback_ = cb;
}

void GlutDisplay::RegisterCursorCallback(std::function<void(int, int)> cb) {

    cursor_callback_ = cb;
}

void GlutDisplay::RegisterDrawCallback(std::function<void()> cb) {

    draw_callback_ = cb;
}

void GlutDisplay::RegisterUpdateCallback(std::function<void(double)> cb) {

    update_callback_ = cb;
}

// C++ callbacks
void GlutDisplay::Reshape(int w, int h) {

    window_width_ = w;
    window_height_ = h;
    glViewport(0, 0, window_width_, window_height_);

    UpdateViewport();
}

void GlutDisplay::UpdateViewport() {

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(0, window_width_, window_height_, 0, -1, 1);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

void GlutDisplay::UpdateCursor(int x, int y) {

    if (x != cursor_x_ || y != cursor_y_) {
        cursor_x_ = x;
        cursor_y_ = y;
        if (cursor_callback_ != 0) {
            cursor_callback_(cursor_x_, cursor_y_);
        }
    }
}

void GlutDisplay::Visibility(int state) {
// TODO:
    (void)state;
}

void GlutDisplay::Keyboard(int key, int x, int y) {

    UpdateCursor(x, y);
    if (keyboard_callback_ != 0) {
        keyboard_callback_(key);
    }
}

void GlutDisplay::Cursor(int x, int y) {

    cursor_x_ = x;
    cursor_y_ = y;
    if (cursor_callback_ != 0) {
        cursor_callback_(cursor_x_, cursor_y_);
    }
}

void GlutDisplay::MouseButton(int button, int state, int x, int y) {

    UpdateCursor(x, y);
    if (mouse_callback_ != 0) {
        mouse_callback_(button, state);
    }
}

void GlutDisplay::Draw() {

    glClear(GL_COLOR_BUFFER_BIT);

    if (draw_callback_ != 0) {
        draw_callback_();
    }

    glutSwapBuffers();
    glutPostRedisplay();
}

void GlutDisplay::Idle() {

    if (update_callback_ != 0) {
        // TODO : put delta time in argument.
        update_callback_(0.0);
    }
}

