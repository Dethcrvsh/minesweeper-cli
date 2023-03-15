#include "graphics_handler.h"
#include <sys/ioctl.h>
#include <unistd.h>
#include <iostream>

GraphicsHandler::GraphicsHandler(int board_width, int board_height, Renderer *renderer) 
    : board_width(board_width * 2), board_height(board_height), renderer(renderer) {

    draw_board(0, 0);
    set_term_dim();
} 

void GraphicsHandler::set_term_dim() {
    // Check the terminal size
    struct winsize size;
    ioctl(STDOUT_FILENO, TIOCGWINSZ, &size);

    this->term_width = size.ws_col;
    this->term_height = size.ws_row;
}

void GraphicsHandler::draw_to_board(int x, int y, std::string text) const {
    auto coords = abs_to_board(x, y);
    renderer->draw(coords.first, coords.second, text);
}

std::pair<int, int> GraphicsHandler::abs_to_board(int x, int y) const {
    return {x * (CELL_SIZE + 1) * 2 + 2, y * (CELL_SIZE + 1) + 1};
}

void GraphicsHandler::draw_box(int x_pos, int y_pos, int width, int height) const {
    // Draw the corners
    renderer->draw(x_pos, y_pos, this->TOP_LEFT);
    renderer->draw(x_pos + width - 1, y_pos, this->TOP_RIGHT);
    renderer->draw(x_pos, y_pos + height - 1, this->BOTTOM_LEFT);
    renderer->draw(x_pos + width - 1, y_pos + height - 1, this->BOTTOM_RIGHT);

    // Draw the horizontal lines
    for (int y : {0, height - 1}) {
        for (int x = 1; x < width - 1; x++) {
            renderer->draw(x + x_pos, y + y_pos, this->HORIZONTAL);
        }
    }

    // Draw the vertical lines
    for (int x : {0, width - 1}) {
        for (int y = 1; y < height - 1; y++) {
            renderer->draw(x + x_pos, y + y_pos, this->VERTICAL);
        }
    }
}

void GraphicsHandler::draw_board(int x_pos, int y_pos) const {
    // Draw the corners
    const int width = this->board_width * (1 + this->CELL_SIZE);
    const int height = this->board_height * (1 + this->CELL_SIZE);

    renderer->draw(x_pos, y_pos, this->TOP_LEFT);
    renderer->draw(x_pos + width, y_pos, this->TOP_RIGHT);
    renderer->draw(x_pos, y_pos + height, this->BOTTOM_LEFT);
    renderer->draw(x_pos + width, y_pos + height, this->BOTTOM_RIGHT);

    // Draw left vertical
    for (int y = 1; y < height; y++) {
        if (y % (1 + this->CELL_SIZE) == 0) {
            renderer->draw(x_pos, y_pos + y, this->VERTICAL_LEFT);
        } else {
            renderer->draw(x_pos, y_pos + y, this->VERTICAL);
        }
    }

    // Draw right vertical
    for (int y = 1; y < height; y++) {
        if (y % (1 + this->CELL_SIZE) == 0) {
            renderer->draw(x_pos + width, y_pos + y, this->VERTICAL_RIGHT);
        } else {
            renderer->draw(x_pos + width, y_pos + y, this->VERTICAL);
        }
    }

    // Draw top horizontal
    for (int x = 1; x < width; x++) {
        if (x % ((1 + this->CELL_SIZE) * 2) == 0) {
            renderer->draw(x_pos + x, y_pos, this->HORIZONTAL_TOP);
        } else {
            renderer->draw(x_pos + x, y_pos, this->HORIZONTAL);
        }
    }

    // Draw bottom horizontal
    for (int x = 1; x < width; x++) {
        if (x % ((1 + this->CELL_SIZE) * 2) == 0) {
            renderer->draw(x_pos + x, y_pos + height, this->HORIZONTAL_BOTTOM);
        } else {
            renderer->draw(x_pos + x, y_pos + height, this->HORIZONTAL);
        }
    }

    // Draw vertical lines
    for (int x = (1 + CELL_SIZE) * 2; x < width; x += (1 + CELL_SIZE) * 2) {
        for (int y = 1; y < height; y++) {
            renderer->draw(x, y, VERTICAL);
        }
    }

    // Draw horizontal lines
    for (int y = 1 + CELL_SIZE; y < height; y += 1 + CELL_SIZE) {
        for (int x = 1; x < width; x++) {
            renderer->draw(x, y, HORIZONTAL);
        }
    }

    // Draw crosses
    for (int y = 1 + CELL_SIZE; y < height; y += 1 + CELL_SIZE) {
        for (int x = (1 + CELL_SIZE) * 2; x < width; x += (1 + CELL_SIZE) * 2) {
            renderer->draw(x, y, MIDDLE);
        }
    }
}


