#include "minesweeper.h"
#include <iostream>

Minesweeper::Minesweeper(int width, int height, int bombs) 
    : width(width), height(height) {
    board = new Board(width, height, bombs);
    renderer = new Renderer(&std::cout);
    g_handler = new GraphicsHandler(board, renderer);
    k_obs = new KeyObserver();

    // Start listening for keystrokes
    k_obs->add_listener(this, Minesweeper::key_listener);
    k_obs->start_listening();
}

Minesweeper::~Minesweeper() {
    delete board;
    delete renderer;
}

void Minesweeper::key_listener(void* object, char key) {
    Minesweeper* that = (Minesweeper*) object;
    that->on_key_press(key);
}

void Minesweeper::on_key_press(char key) {
    if (key == 'q') {
        k_obs->end_listening();
    }

    auto key_it = keybinds.keybinds.find(key);

    // Ignore if the key cannot be found in the map
    if (key_it == keybinds.keybinds.end()) {
        return;
    }

    Action action = key_it->second;
    
    switch(action) {
        case MOVE_LEFT  :   g_handler->move_selection(-1, 0);     break;
        case MOVE_RIGHT :   g_handler->move_selection(1, 0);      break;
        case MOVE_UP    :   g_handler->move_selection(0, -1);     break;
        case MOVE_DOWN  :   g_handler->move_selection(0, 1);      break;
        case UNCOVER    :   board->uncover(g_handler->selection_x, g_handler->selection_y);     break;
    }

    g_handler->draw();
}

/*void Minesweeper::draw() const {
    for (int x = 0; x < width; x++) {
        for (int y = 0; y < height; y++) {
            auto square = board->get_square(x, y);

            if (square->is_bomb) {
                g_handler->draw_to_board(x, y, "\033[1;37m💣\033[0m");
            } 
            if (square->count == 1) {
                g_handler->draw_to_board(x, y, "\033[1;34m1\033[0m");
            }
            if (square->count == 2) {
                g_handler->draw_to_board(x, y, "\033[1;32m2\033[0m");
            }
            if (square->count == 3) {
                g_handler->draw_to_board(x, y, "\033[1;31m3\033[0m");
            }
            if (square->count == 4) {
                g_handler->draw_to_board(x, y, "\033[1;35m4\033[0m");
            }
        }
    }
}*/
