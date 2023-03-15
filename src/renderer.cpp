#include "renderer.h"
#include <iostream>
#include <stdlib.h>
#include <string>
#include <unistd.h>

Renderer::Renderer(int board_width, int board_height, std::ostream *stream)
    : board_width(board_width * 2), board_height(board_height), stream(stream) {

    this->hide_cursor();
    this->clear();
    this->draw_board(0, 0);
}

Renderer::~Renderer() {
    this->show_cursor();
    this->clear();
    this->reset_cursor();
}

void Renderer::draw_to_board(int x, int y, std::string text) const {
    auto coords = abs_to_board(x, y);
    draw(coords.first, coords.second, text);
}

void Renderer::ansi_command(std::string &command) const {
    *this->stream << this->ESC << this->CONTROL_SEQ << command;
}

void Renderer::show_cursor() const {
    std::string command = "?25h";
    this->ansi_command(command);
}

void Renderer::hide_cursor() const {
    std::string command = "?25l";
    this->ansi_command(command);
}

void Renderer::move_cursor(int x, int y) const {
    std::string command = "";
    command.append(std::to_string(y + 1))
        .append(";")
        .append(std::to_string(x + 1))
        .append("f");
    this->ansi_command(command);
}

void Renderer::reset_cursor() const {
    std::string command = "H";
    this->ansi_command(command);
}

void Renderer::clear() const {
    std::string command = "2J";
    this->ansi_command(command);
}

void Renderer::draw(int x, int y, std::string text) const {
    this->move_cursor(x, y);
    *this->stream << text;
}

void Renderer::draw_box(int x_pos, int y_pos, int width, int height) const {
    // Draw the corners
    this->draw(x_pos, y_pos, this->TOP_LEFT);
    this->draw(x_pos + width - 1, y_pos, this->TOP_RIGHT);
    this->draw(x_pos, y_pos + height - 1, this->BOTTOM_LEFT);
    this->draw(x_pos + width - 1, y_pos + height - 1, this->BOTTOM_RIGHT);

    // Draw the horizontal lines
    for (int y : {0, height - 1}) {
        for (int x = 1; x < width - 1; x++) {
            this->draw(x + x_pos, y + y_pos, this->HORIZONTAL);
        }
    }

    // Draw the vertical lines
    for (int x : {0, width - 1}) {
        for (int y = 1; y < height - 1; y++) {
            this->draw(x + x_pos, y + y_pos, this->VERTICAL);
        }
    }
}

void Renderer::draw_board(int x_pos, int y_pos) const {
    // Draw the corners

    const int width = this->board_width * (1 + this->CELL_SIZE);
    const int height = this->board_height * (1 + this->CELL_SIZE);

    this->draw(x_pos, y_pos, this->TOP_LEFT);
    this->draw(x_pos + width, y_pos, this->TOP_RIGHT);
    this->draw(x_pos, y_pos + height, this->BOTTOM_LEFT);
    this->draw(x_pos + width, y_pos + height, this->BOTTOM_RIGHT);

    // Draw left vertical
    for (int y = 1; y < height; y++) {
        if (y % (1 + this->CELL_SIZE) == 0) {
            this->draw(x_pos, y_pos + y, this->VERTICAL_LEFT);
        } else {
            this->draw(x_pos, y_pos + y, this->VERTICAL);
        }
    }

    // Draw right vertical
    for (int y = 1; y < height; y++) {
        if (y % (1 + this->CELL_SIZE) == 0) {
            this->draw(x_pos + width, y_pos + y, this->VERTICAL_RIGHT);
        } else {
            this->draw(x_pos + width, y_pos + y, this->VERTICAL);
        }
    }

    // Draw top horizontal
    for (int x = 1; x < width; x++) {
        if (x % ((1 + this->CELL_SIZE) * 2) == 0) {
            this->draw(x_pos + x, y_pos, this->HORIZONTAL_TOP);
        } else {
            this->draw(x_pos + x, y_pos, this->HORIZONTAL);
        }
    }

    // Draw bottom horizontal
    for (int x = 1; x < width; x++) {
        if (x % ((1 + this->CELL_SIZE) * 2) == 0) {
            this->draw(x_pos + x, y_pos + height, this->HORIZONTAL_BOTTOM);
        } else {
            this->draw(x_pos + x, y_pos + height, this->HORIZONTAL);
        }
    }

    // Draw vertical lines
    for (int x = (1 + CELL_SIZE) * 2; x < width; x += (1 + CELL_SIZE) * 2) {
        for (int y = 1; y < height; y++) {
            draw(x, y, VERTICAL);
        }
    }

    // Draw horizontal lines
    for (int y = 1 + CELL_SIZE; y < height; y += 1 + CELL_SIZE) {
        for (int x = 1; x < width; x++) {
            draw(x, y, HORIZONTAL);
        }
    }

    // Draw crosses
    for (int y = 1 + CELL_SIZE; y < height; y += 1 + CELL_SIZE) {
        for (int x = (1 + CELL_SIZE) * 2; x < width; x += (1 + CELL_SIZE) * 2) {
            draw(x, y, MIDDLE);
        }
    }
}

std::pair<int, int> Renderer::abs_to_board(int x, int y) const {
    return {x * (CELL_SIZE + 1) * 2 + 2, y * (CELL_SIZE + 1) + 1};
}
