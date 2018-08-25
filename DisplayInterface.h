#ifndef DISPLAY_INTERFACE_H_
#define DISPLAY_INTERFACE_H_

#include <string>
#include <functional>

class DisplayInterface {
public:
    virtual ~DisplayInterface() {}
    virtual void SetClearColor(float r, float g, float b, float a=1.0) = 0;
    virtual void SetWindowName(std::string name) = 0;
    virtual void SetWindowSize(int w, int h) = 0;
    virtual void SetWindowPosition(int x, int y) = 0;
    virtual void Init(int argc, char** argv) = 0;
    virtual void Run() = 0;

    virtual void AddMouseButtonHandler(std::function<bool(int, int, int)> & handler) = 0;
    virtual void AddCursorPositionHandler(std::function<bool(int, int)> & handler) = 0;
    virtual void AddKeyboardHandler(std::function<bool(int, bool, bool)> handler) = 0;
    virtual void AddRenderer(std::function<bool()> renderer) = 0;
    virtual void AddUpdater(std::function<bool(double)> & updater) = 0;
};

#endif  // DISPLAY_INTERFACE_H_
