#ifndef GLFW_DISPLAY_H_
#define GLFW_DISPLAY_H_

#include "DisplayCommon.h"

class GlfwDisplay : public DisplayCommon {
private: // static methods

public:
    GlfwDisplay();
    ~GlfwDisplay();
    void Init(int argc, char ** argv);
    void Run();
    
};

#endif // GLFW_DISPLAY_H_

