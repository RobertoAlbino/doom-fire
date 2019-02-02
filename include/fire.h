#pragma once

namespace DoomFire {

class Fire {
    private:
        void createFireDataStructure();
    public:
        const static int fireWidth = 2;
        const static int fireHeigth = 3;
        int fireArray[fireWidth][fireHeigth];
        void start();
        void calculateFirePropagation();
        void renderFire();
    };
}


