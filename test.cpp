#include "DisplayFactory.h"

#include <functional>

void key_callback(int key) {

    switch(key) {
    case 27:
    case 'q':
        exit(0); break;
    default:
        break;
    }
}

void draw_callback() {
}

int main(int argc, char** argv) {

    DisplayInterface* display = DisplayFactory::getGlutDisplay();

    display->SetWindowName("test");
    display->SetWindowSize(800, 800);
    display->SetWindowPosition(100, 100);
    display->SetClearColor(0.0, 0.0, 0.0, 1.0);

    {
        using namespace std::placeholders;
        display->RegisterKeyboardCallback( std::bind(key_callback, _1) );
        display->RegisterDrawCallback( std::bind(draw_callback) );
    }

    display->Init(argc, argv);

    display->Run();

    return 0;
}

