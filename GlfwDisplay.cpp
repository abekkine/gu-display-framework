#include "GlfwDisplay.h"

#include <GLFW/glfw3.h>

GlfwDisplay::GlfwDisplay() {}

GlfwDisplay::~GlfwDisplay() {}

void GlfwDisplay::Init(int argc, char **argv) {
    (void)argc;
    (void)argv;

    if (!glfwInit()) {
        throw std::string("Unable to initialize GLFW!");
    }

    glfwWindowHint(GLFW_SAMPLES, 8);
}

void GlfwDisplay::Run() {
}

