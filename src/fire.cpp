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
        Console console;
        console.refresh();
    }
}


