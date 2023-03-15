#include "board.h"
#include "key_observer.h"
#include <iostream>

int main() {
    int width = 30;
    int height = 16;

    Renderer *renderer = new Renderer(width, height, &std::cout);
    Board *board = new Board(width, height, 99);

    for (int x = 0; x < width; x++) {
        for (int y = 0; y < height; y++) {
            auto square = board->get_square(x, y);

            if (square->is_bomb) {
                renderer->draw_to_board(x, y, "\033[1;37m💣\033[0m");
            } 
            if (square->count == 1) {
                renderer->draw_to_board(x, y, "\033[1;34m1\033[0m");
            }
            if (square->count == 2) {
                renderer->draw_to_board(x, y, "\033[1;32m2\033[0m");
            }
            if (square->count == 3) {
                renderer->draw_to_board(x, y, "\033[1;31m3\033[0m");
            }
            if (square->count == 4) {
                renderer->draw_to_board(x, y, "\033[1;35m4\033[0m");
            }
        }
    }

    system("stty raw");
    while(1) {
        char c = getchar();

        if (c == 'q') {
            break;
        }
    }

    delete renderer;
    delete board;

    return 0;
}

 
