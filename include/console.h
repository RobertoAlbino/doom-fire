#pragma once

#include <ctime>
#include <string>
#include <sstream>
#include <ncurses.h>

namespace DoomFire {

class Console {
private:
    struct COLOR {
        short foreground, background;
        bool foreBold, backBold;
    };
    clock_t throttleLast;
    bool throttleInitialized;
    static int classInstances;
    Console(const Console &);
    Console & operator= (const Console &);
    static bool foreBoldFlags[256];
public:
    typedef unsigned char COLOR_ID;
    typedef struct COORD_2D {
        int x, y;
    } COORD2D, COORD2;
    Console();
    ~Console();
    void initColor(COLOR_ID colorId, int fg, int bg, bool fBold, bool bBold);
    COORD_2D getWindowSize();
    COORD_2D getCurPos();
    void cls();
    void moveCursor(int x, int y);
    void moveCursor(COORD_2D pos);
    void color(COLOR_ID);

    template <typename TYPE>
    std::string toString(TYPE t) {
        std::stringstream ss;
        ss << t;
        return ss.str();
    }

    void output(std::string s);

    template <typename TYPE>
    void output(TYPE t) {
        output(toString(t));
    }

    template <typename TYPE>
    void output(COLOR_ID c, TYPE t) {
        color(c);
        output(t);
    }

    template <typename TYPE>
    void output(int x, int y, TYPE t) {
        moveCursor(x, y);
        output(t);
    }

    template <typename TYPE>
    void output(COORD_2D pos, TYPE t) {
        moveCursor(pos);
        output(t);
    }

    template <typename TYPE>
    void output(int x, int y, COLOR_ID c, TYPE t) {
        moveCursor(x, y);
        color(c);
        output(t);
    }

    template <typename TYPE>
    void output(COORD_2D pos, COLOR_ID c, TYPE t) {
        moveCursor(pos);
        color(c);
        output(t);
    }

    int getKey();
    int waitForKey();
    int waitForNewKey();
    void waitForKey(int match);
    int echoKey();
    int waitForChar();
    std::string waitForInput();
    std::string waitForInput(char delimiter);
    std::string waitForInput(std::string delimiter);

    template <typename TYPE>
    TYPE waitForInput(std::string delimiters) {
        std::string str(waitForInput(delimiters));
        std::stringstream ss;
        TYPE result;

        ss << str;
        ss >> result;
        return result;
    }

    template <typename TYPE>
    TYPE waitForInput(char delimiter) {
        return waitForInput<TYPE>(std::string(1, delimiter));
    }

    template <typename TYPE>
    TYPE waitForInput() {
        return waitForInput<TYPE>("\n");
    }

    void sleepMs(long ms);
    void throttle(long ms);
    void clearKey();
    void pause();

    template <typename TYPE>
    Console& operator<< (TYPE t) {
        output(t);
        return *this;
    }

    template <typename TYPE>
    Console& operator>> (TYPE& t) {
        t = waitForInput < TYPE > ();
        return *this;
    }
};
static Console con;
} // namespace DoomFire



