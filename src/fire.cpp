#include <iostream>
#include "../include/fire.h"
#include "../include/console.h"

namespace DoomFire {

    void Fire::start() {
        createFireDataStructure();
    }

    void Fire::createFireDataStructure() {
        const int totalPixels = fireWidth * fireHeigth;
        for (int i = 0; i < totalPixels; i++) {
            fireArray[i][i] = 0;
        }
        renderFire();
    }

    void Fire::renderFire() {
        for (int row = 0; row < fireHeigth; row++) {
            DoomFire::Console console;
        }
    }

}


