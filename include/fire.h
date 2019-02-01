#ifndef DOOMFIRE_FIRE_H
#define DOOMFIRE_FIRE_H
#endif

namespace DoomFire {

    class Fire {
        public:
            const static int fireWidth = 2;
            const static int fireHeigth = 3;
            int fireArray[fireWidth][fireHeigth];
            void start();
            void createFireDataStructure();
            void calculateFirePropagation();
            void renderFire();
    };
}


