#include "minesweeper.h"
#include <iostream>

Minesweeper::Minesweeper(int width, int height, int bombs) 
    : width(width), height(height) {
    this->board = new Board(width, height, bombs);
    this->renderer = new Renderer(width, height, &std::cout);
    this->k_obs = new KeyObserver();

    this->k_obs->add_listener(this, Minesweeper::key_listener);
    this->k_obs->start_listening();
}

Minesweeper::~Minesweeper() {
    delete this->board;
    delete this->renderer;
}

void Minesweeper::key_listener(void* object, char key) {
    Minesweeper* that = (Minesweeper*) object;
    that->on_key_press(key);
}

void Minesweeper::on_key_press(char key) {
    if (key == 'q') {
        this->k_obs->end_listening();
    }

    this->draw();
}

void Minesweeper::draw() const {
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
}
