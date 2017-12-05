#ifndef DISPLAY_INTERFACE_H_
#define DISPLAY_INTERFACE_H_

#include <string>
#include <functional>

class DisplayInterface {
public:
    virtual ~DisplayInterface() {}
    virtual void SetClearColor(float r, float g, float b, float a=1.0) = 0;
    virtual void SetWindowName(std::string) = 0;
    virtual void SetWindowSize(int w, int h) = 0;
    virtual void SetWindowPosition(int x, int y) = 0;
    virtual void Init(int argc, char** argv) = 0;
    virtual void Run() = 0;

    virtual void RegisterMouseCallback( std::function<void(int, int)> cb ) = 0;
    virtual void RegisterCursorCallback( std::function<void(int, int)> cb ) = 0;
    virtual void RegisterKeyboardCallback(std::function<void(int)> cb) = 0;
    virtual void RegisterDrawCallback( std::function<void()> cb ) = 0;
    virtual void RegisterUpdateCallback( std::function<void(double)> cb ) = 0;
};

#endif  // DISPLAY_INTERFACE_H_

