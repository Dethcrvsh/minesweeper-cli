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
    // TODO: Move selection, it is probably in the wrong class
    
    switch(action) {
        case MOVE_LEFT  :   board->move_selection(-1, 0);     break;
        case MOVE_RIGHT :   board->move_selection(1, 0);      break;
        case MOVE_UP    :   board->move_selection(0, -1);     break;
        case MOVE_DOWN  :   board->move_selection(0, 1);      break;
        case FLAG       :   board->set_flag();                break; 
        case UNCOVER    :   board->uncover();                 break;
    }

    g_handler->draw();
}
