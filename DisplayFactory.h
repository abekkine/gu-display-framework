#ifndef DISPLAY_FACTORY_H_
#define DISPLAY_FACTORY_H_

#include "DisplayInterface.h"
#include "GlutDisplay.h"

class DisplayFactory {
public:
    static DisplayInterface * getGlutDisplay() {

        return new GlutDisplay();
    }

    static DisplayInterface * getGLFWDisplay() {

        return 0;
    }
};

#endif // DISPLAY_FACTORY_H_

