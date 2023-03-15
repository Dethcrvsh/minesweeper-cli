#include "minesweeper.h"
#include <iostream>

int main() {
    int width = 30;
    int height = 16;
    int bombs = 99;

    auto ms = new Minesweeper(width, height, bombs);

    delete ms;

    return 0;
}
