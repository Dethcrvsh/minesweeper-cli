#ifndef _MINESWEEPER
#define _MINESWEEPER

#include "board.h"
#include "renderer.h"
#include "key_observer.h"

class Minesweeper {
public:
    Minesweeper(int width, int height, int bombs);
    ~Minesweeper();

    // A static key listener that delegates the
    // key presses to the right object
    static void key_listener(void* object, char c);

    void on_key_press(char key);

private:
    int width;
    int height;

    Board *board;
    Renderer *renderer;
    KeyObserver *k_obs;

    //TODO: Probably remove this
    void draw() const;
};

#endif
