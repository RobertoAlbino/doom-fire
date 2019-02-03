#include "../include/console.h"
#include <curses.h>
#include <curses.h>

namespace DoomFire {

    int Console::classInstances = 0;
    bool Console::foreBoldFlags[256];
    int posix_translateKey();

    DoomFire::Console::Console() {
        throttleInitialized = false;
        if (classInstances == 0) {
            initscr();
            cbreak();
            noecho();
            keypad(stdscr, true);
            start_color();
            cls();
            for (int i = 0; i < 256; i++) {
                foreBoldFlags[i] = false;
            }
        }
        ++classInstances;
    }

    DoomFire::Console::~Console(void) {
        --classInstances;
        if (classInstances == 0) {
            cls();
            endwin();
        }
    }

    void Console::initColor(COLOR_ID colorId, int fg, int bg, bool fBold, bool bBold) {
        if (bBold) {
            init_pair(colorId + 1, fg, bg + 8);
        } else {
            init_pair(colorId + 1, fg, bg);
        }
        foreBoldFlags[colorId] = fBold;
    }

    Console::COORD_2D Console::getWindowSize() {
        return {COLS, LINES};
    }

    Console::COORD_2D Console::getCurPos() {
        return {getcurx(stdscr), getcury(stdscr)};
    }

    void Console::cls() {
        clear();
    }

    void Console::moveCursor(int x, int y) {
        move(y, x);
    }

    void Console::moveCursor(COORD_2D pos) {
        moveCursor(pos.x, pos.y);
    }

    void Console::color(COLOR_ID colorId) {
        if (foreBoldFlags[colorId]) {
            attrset(COLOR_PAIR(colorId + 1) | A_BOLD);
        }
        else
            attrset(COLOR_PAIR(colorId + 1));
    }

    void Console::output(std::string s) {
        printw("%s", s.c_str());
    }

    std::string Console::waitForInput() {
        return waitForInput("\n");
    }

    std::string Console::waitForInput(char delineator) {
        return waitForInput(std::string(1, delineator));
    }

    std::string Console::waitForInput(std::string delineators) {
        char input;
        std::string str;

        while (true) {
            COORD_2D pos = getCurPos();
            input = echoKey();

            if (input == '\b') {
                if (!str.empty()) {
                    str.pop_back();
                    if (pos.x == 0) {
                        moveCursor(getWindowSize().x - 1, pos.y - 1);
                    } else {
                        moveCursor(pos.x - 1, pos.y);
                    }
                } else {
                    moveCursor(pos.x, pos.y);
                }
                pos = getCurPos();
                output(' ');
                moveCursor(pos.x, pos.y);
            } else {
                for (size_t i = 0; i < delineators.length(); ++i)
                    if (input == delineators.at(i))
                        goto soSueMe;
                str += input;
            }
        }
        soSueMe:

        if (input != '\n') {
            while (echoKey() != '\n');
        }

        return str;
    }

    int Console::getKey() {
        timeout(0);
        return posix_translateKey();
    }

    int Console::waitForKey() {
        timeout(-1);
        return posix_translateKey();
    }

    int Console::waitForNewKey() {
        clearKey();
        return waitForKey();
    }

    int posix_translateKey() {
        int ch = getch();
        if (ch == ERR) return 0;
        if (ch == '\r') return '\n';
    }

    void Console::waitForKey(int match) {
        while (waitForKey() != match);
    }

    int Console::echoKey() {
        int i = waitForKey();
        output((char)i);
        return i;
    }

    void Console::sleepMs(long ms) {
        timespec sleepFor = { ms / 1000, ms % 1000 * 1000000 };
        nanosleep(&sleepFor, NULL);
    }

    void Console::throttle(long ms) {
        if (throttleInitialized) {
            throttleLast += ms / 1000.0 * CLOCKS_PER_SEC;
            if (throttleLast > clock())
                sleepMs(throttleLast - clock());
        }
        else {
            throttleLast = clock();
            throttleInitialized = true;
        }
    }

    void Console::clearKey() {
        while (getKey());
    }

    void Console::pause() {
        clearKey();
        output("Press any key to continue . . .");
        waitForKey();
        output("\n");
    }
}


