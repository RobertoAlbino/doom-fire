#include <iostream>
#include "../include/fire.h"
#include "../include/console.h"

namespace DoomFire {

    Console console;

    void Fire::start() {
        createFireDataStructure();
    }

    void Fire::createFireDataStructure() {
        const int totalPixels = fireWidth * fireHeigth;
        for (int i = 0; i < totalPixels; i++) {
            fireArray[i][i] = 0;
        }
        console.output("Olá Mundo");
    }

    void Fire::renderFire() {

    }

}


