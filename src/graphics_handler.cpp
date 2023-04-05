#include "graphics_handler.h"
#include <sys/ioctl.h>
#include <unistd.h>
#include <iostream>
#include "board.h"

GraphicsHandler::GraphicsHandler(Board *board, Renderer *renderer)
    : board(board), renderer(renderer) {

    draw_board();
    draw_board_selection();
} 

void GraphicsHandler::draw() const {
    renderer->clear();
    draw_board();
    draw_board_selection();
}

void GraphicsHandler::set_term_dim() {
    // TODO: Fix this
    // Check the terminal size
    struct winsize size;
    ioctl(STDOUT_FILENO, TIOCGWINSZ, &size);

    term_width = size.ws_col;
    term_height = size.ws_row;
}

void GraphicsHandler::draw_to_board(int x, int y, std::string text, Color color) const {
    auto coords = abs_to_board(x, y);

    renderer->start_color(color);
    renderer->draw(coords.first, coords.second, text);
    renderer->reset_color();
}

std::pair<int, int> GraphicsHandler::abs_to_board(int x, int y) const {
    return {
        x * (CELL_SIZE + 1) * 2 + 2 + BOARD_MARGIN_X, 
        y * (CELL_SIZE + 1) + 1 + BOARD_MARGIN_Y
    };
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

void GraphicsHandler::draw_board_selection() const {
    std::pair<int, int> *selection = board->get_selection();
    std::pair<int, int> pos = abs_to_board(selection->first, selection->second);

    renderer->start_color(SELECTION);
    draw_box(pos.first - 2, pos.second - 1, (CELL_SIZE + 2)*2 - 1, CELL_SIZE + 2);
    renderer->reset_color();
}

void GraphicsHandler::draw_board() const {
    draw_board_outline();
    draw_board_content();
}

void GraphicsHandler::draw_board_outline() const {
    renderer->start_color(BOARD_OUTLINE);

    // Draw the corners
    const int width = this->board->get_width() * 2 * (1 + this->CELL_SIZE);
    const int height = this->board->get_height() * (1 + this->CELL_SIZE);

    renderer->draw(BOARD_MARGIN_X , BOARD_MARGIN_Y, this->TOP_LEFT);
    renderer->draw(BOARD_MARGIN_X + width, BOARD_MARGIN_Y, this->TOP_RIGHT);
    renderer->draw(BOARD_MARGIN_X , BOARD_MARGIN_Y+ height, this->BOTTOM_LEFT);
    renderer->draw(BOARD_MARGIN_X + width, BOARD_MARGIN_Y+ height, this->BOTTOM_RIGHT);

    // Draw left vertical
    for (int y = 1; y < height; y++) {
        if (y % (1 + this->CELL_SIZE) == 0) {
            renderer->draw(BOARD_MARGIN_X , BOARD_MARGIN_Y+ y, this->VERTICAL_LEFT);
        } else {
            renderer->draw(BOARD_MARGIN_X , BOARD_MARGIN_Y+ y, this->VERTICAL);
        }
    }

    // Draw right vertical
    for (int y = 1; y < height; y++) {
        if (y % (1 + this->CELL_SIZE) == 0) {
            renderer->draw(BOARD_MARGIN_X + width, BOARD_MARGIN_Y+ y, this->VERTICAL_RIGHT);
        } else {
            renderer->draw(BOARD_MARGIN_X + width, BOARD_MARGIN_Y+ y, this->VERTICAL);
        }
    }

    // Draw top horizontal
    for (int x = 1; x < width; x++) {
        if (x % ((1 + this->CELL_SIZE) * 2) == 0) {
            renderer->draw(BOARD_MARGIN_X + x, BOARD_MARGIN_Y, this->HORIZONTAL_TOP);
        } else {
            renderer->draw(BOARD_MARGIN_X + x, BOARD_MARGIN_Y, this->HORIZONTAL);
        }
    }

    // Draw bottom horizontal
    for (int x = 1; x < width; x++) {
        if (x % ((1 + this->CELL_SIZE) * 2) == 0) {
            renderer->draw(BOARD_MARGIN_X + x, BOARD_MARGIN_Y+ height, this->HORIZONTAL_BOTTOM);
        } else {
            renderer->draw(BOARD_MARGIN_X + x, BOARD_MARGIN_Y+ height, this->HORIZONTAL);
        }
    }

    // Draw vertical lines
    for (int x = (1 + CELL_SIZE) * 2; x < width; x += (1 + CELL_SIZE) * 2) {
        for (int y = 1; y < height; y++) {
            renderer->draw(BOARD_MARGIN_X + x, BOARD_MARGIN_Y+ y, VERTICAL);
        }
    }

    // Draw horizontal lines
    for (int y = 1 + CELL_SIZE; y < height; y += 1 + CELL_SIZE) {
        for (int x = 1; x < width; x++) {
            renderer->draw(BOARD_MARGIN_X + x, BOARD_MARGIN_Y+ y, HORIZONTAL);
        }
    }

    // Draw crosses
    for (int y = 1 + CELL_SIZE; y < height; y += 1 + CELL_SIZE) {
        for (int x = (1 + CELL_SIZE) * 2; x < width; x += (1 + CELL_SIZE) * 2) {
            renderer->draw(BOARD_MARGIN_X + x, BOARD_MARGIN_Y+ y, MIDDLE);
        }
    }
    
    renderer->reset_color();
}

void GraphicsHandler::draw_board_content() const {
    for (int y = 0; y < board->get_height(); y++) {
        for (int x = 0; x < board->get_width(); x++) {
            struct Square *square = board->get_square(x, y);

            if (square->is_flagged) {
                draw_to_board(x, y, "🏴", white);
                continue;
            }

            if (!square->is_open) {
                fill_square(x, y, "█", white);
                continue;
            }

            if (square->is_bomb) {
                draw_to_board(x, y, "💥", red);
            }

            if (square->is_bomb || square->count == 0) {
                continue; 
            }

            draw_to_board(x, y, std::to_string(square->count), NUMBER_COLOR.at(square->count));
        }
    }
}

void GraphicsHandler::fill_square(int x, int y, std::string text, Color color) const {
    auto coords = abs_to_board(x, y);

    // This is such a hack and I hate it
    for (int y = 0; y < CELL_SIZE; y++) {
        for (int x = -1; x < CELL_SIZE*2; x++) {
            renderer->start_color(color);
            renderer->draw(coords.first + x , coords.second + y, text);
            renderer->reset_color();
        }
    } 
}
