#include <iostream>
#include "../include/fire.h"

namespace DoomFire {

    void Fire::createFireDataStructure() {
        std::cout << "Largura do fogo: " <<  Fire::fireWidth  << std::endl;
        std::cout << "Altura do fogo: "  <<  Fire::fireHeigth << std::endl;
    }
}


