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
    display_instance_->Keyboard((int)key, true, false, x, y);
}

void GlutDisplay::keyboard_up_func(unsigned char key, int x, int y) {
    display_instance_->Keyboard((int)key, false, false, x, y);
}

void GlutDisplay::special_func(int key, int x, int y) {
    display_instance_->Keyboard(key, true, true, x, y);
}

void GlutDisplay::special_up_func(int key, int x, int y) {
    display_instance_->Keyboard(key, false, true, x, y);
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

void GlutDisplay::Init(int argc, char ** argv) {
    DisplayCommon::Init(argc, argv);

    if (display_instance_ == 0) {
        display_instance_ = this;
    }

    glutInit(&arg_count_, arg_values_);

    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize(window_width_, window_height_);
    glutInitWindowPosition(window_left_, window_top_);
    glutCreateWindow(window_name_.c_str());

    glutReshapeFunc(reshape_func);
    glutVisibilityFunc(visibility_func);
    glutKeyboardFunc(keyboard_func);
    glutKeyboardUpFunc(keyboard_up_func);
    glutSpecialFunc(special_func);
    glutSpecialUpFunc(special_up_func);
    glutDisplayFunc(display_func);
    glutMotionFunc(motion_func);
    glutPassiveMotionFunc(motion_func);
    glutIdleFunc(idle_func);
    glutMouseFunc(mouse_func);

    glClearColor(
        clear_color_[0],
        clear_color_[1],
        clear_color_[2],
        clear_color_[3]);
}

void GlutDisplay::Run() {
    glutMainLoop();
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
        for (int i=0; i<num_cursor_position_handlers_; ++i) {
            bool process_next = cursor_position_handlers_[i](cursor_x_, cursor_y_);
            if (process_next == false) break;
        }
    }
}

void GlutDisplay::Visibility(int state) {
    // TODO:
    (void)state;
}

void GlutDisplay::Keyboard(int key, bool pressed, bool special, int x, int y) {
    UpdateCursor(x, y);
    for (int i=0; i<num_keyboard_handlers_; ++i) {
        bool process_next = keyboard_handlers_[i](key, pressed, special);
        if (process_next == false) break;
    }
}

void GlutDisplay::Cursor(int x, int y) {
    cursor_x_ = x;
    cursor_y_ = y;
    for (int i=0; i<num_cursor_position_handlers_; ++i) {
        bool process_next = cursor_position_handlers_[i](cursor_x_, cursor_y_);
        if (process_next == false) break;
    }
}

void GlutDisplay::MouseButton(int button, int state, int x, int y) {
    UpdateCursor(x, y);
    for (int i=0; i<num_mouse_button_handlers_; ++i) {
        // TODO : extract and feed modifiers below. -----------------v
        bool process_next = mouse_button_handlers_[i](button, state, 0);
        if (process_next == false) break;
    }
}

void GlutDisplay::Draw() {
    glClear(GL_COLOR_BUFFER_BIT);

    for (int i=0; i<num_renderers_; ++i) {
        bool render_next = renderers_[i]();
        if (render_next == false) break;
    }

    glutSwapBuffers();
    glutPostRedisplay();
}

void GlutDisplay::Idle() {
    for (int i=0; i<num_updaters_; ++i) {
        // TODO : use delta time -------v
        bool update_next = updaters_[i](0.2);
        if (update_next == false) break;
    }
}
