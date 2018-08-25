#ifndef DISPLAY_COMMON_H_
#define DISPLAY_COMMON_H_

#ifndef MAX_CONTAINER
#define MAX_CONTAINER 32
#endif

#include "DisplayInterface.h"

class DisplayCommon : public DisplayInterface {
public:
    DisplayCommon() {
        num_mouse_button_handlers_ = 0;
        num_cursor_position_handlers_ = 0;
        num_keyboard_handlers_ = 0;
        num_renderers_ = 0;
        num_updaters_ = 0;
    }
    ~DisplayCommon() {}
    void SetClearColor(float r, float g, float b, float a) {
        clear_color_[0] = r;
        clear_color_[1] = g;
        clear_color_[2] = b;
        clear_color_[3] = a;
    }
    void SetWindowName(std::string name) {
        window_name_ = name;
    }
    void SetWindowSize(int w, int h) {
        window_width_ = w;
        window_height_ = h;
    }
    void SetWindowPosition(int x, int y) {
        window_left_ = x;
        window_top_ = y;
    }
    void Init(int argc, char** argv) {
        arg_count_ = argc;
        arg_values_ = argv;
    }
    void Run() {

    }
    void AddMouseButtonHandler(std::function<bool(int, int, int)> & handler) {
        if (num_mouse_button_handlers_ == MAX_CONTAINER) {
            throw std::string("Maximum number of mouse button handlers reached!");
        }
        mouse_button_handlers_[num_mouse_button_handlers_++] = handler;
    }
    void AddCursorPositionHandler(std::function<bool(int, int)> & handler) {
        if (num_cursor_position_handlers_ == MAX_CONTAINER) {
            throw std::string("Maximum number of cursor position handlers reached!");
        }
        cursor_position_handlers_[num_cursor_position_handlers_++] = handler;
    }
    void AddKeyboardHandler(std::function<bool(int, bool, bool)> handler) {
        if (num_keyboard_handlers_ == MAX_CONTAINER) {
            throw std::string("Maximum number of keyboard handlers reached!");
        }
        keyboard_handlers_[num_keyboard_handlers_++] = handler;
    }
    void AddRenderer(std::function<bool()> renderer) {
        if (num_renderers_ == MAX_CONTAINER) {
            throw std::string("Maximum number of renderers reached!");
        }
        renderers_[num_renderers_++] = renderer;
    }
    void AddUpdater(std::function<bool(double)> & updater) {
        if (num_updaters_ == MAX_CONTAINER) {
            throw std::string("Maximum number of updaters reached!");
        }
        updaters_[num_updaters_++] = updater;
    }

protected:
    float clear_color_[4];
    std::string window_name_;
    int window_width_;
    int window_height_;
    int window_left_;
    int window_top_;
    int cursor_x_;
    int cursor_y_;
    int arg_count_;
    char ** arg_values_;
    int num_mouse_button_handlers_;
    int num_cursor_position_handlers_;
    int num_keyboard_handlers_;
    int num_renderers_;
    int num_updaters_;
    std::function<bool(int, int, int)> mouse_button_handlers_[MAX_CONTAINER];
    std::function<bool(int, int)> cursor_position_handlers_[MAX_CONTAINER];
    std::function<bool(int, bool, bool)> keyboard_handlers_[MAX_CONTAINER];
    std::function<bool()> renderers_[MAX_CONTAINER];
    std::function<bool(double)> updaters_[MAX_CONTAINER];
};

#endif // DISPLAY_COMMON_H_
