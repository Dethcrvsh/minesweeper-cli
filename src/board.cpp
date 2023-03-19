#include "board.h"
#include "renderer.h"
#include <iostream>
#include <stdlib.h>
#include <time.h>

Board::Board(int width, int height, int bombs)
    : width(width), height(height), bombs(bombs) {

    init_board();
    
    populated = false;

    selection.first = 0;
    selection.second = 0;
}

void Board::init_board() {
    // Initialize the board
    for (int y = 0; y < height; y++) {
        std::vector<struct Square> row;
        for (int x = 0; x < width; x++) {
            row.push_back({false, false, 0});
        }
    this->board.push_back(row);
    }
}

int Board::get_width() const { return width; }

int Board::get_height() const { return height; }

std::pair<int, int>* Board::get_selection() {
    return &selection;
}

void Board::uncover() {
    if (!populated) {
        populated = true;
        populate_bombs(selection.first, selection.second, SAFE_RADIUS);
        calculate_numbers();    
    }

    struct Square *square = get_square(selection.first, selection.second);

    if (square->count == 0) {
        uncover_empty_neighbours(selection.first, selection.second);
    }

    get_square(selection.first, selection.second)->is_open = true;
}

void Board::uncover_empty_neighbours(int x, int y) {
    struct Square *square = get_square(x, y);

    square->is_open = true;

    if (square->count > 0 || square->is_bomb) {
        return;
    }

    for (auto neighbour : get_neighbours(x, y)) {
        struct Square *neigh_square = get_square(neighbour.first, neighbour.second);

        if (!neigh_square->is_open) {
            uncover_empty_neighbours(neighbour.first, neighbour.second);
        }
    }
}

void Board::move_selection(int x, int y) {
    selection.first += x;
    selection.second += y;
}

void Board::set_flag() {
    struct Square *square = get_square(selection.first, selection.second);
    square->is_flagged = !square->is_flagged;
}

void Board::populate_bombs(int safe_x, int safe_y, int safe_radius) {
    // Generate random seed
    srand(time(NULL));

    int bomb_count = 0;

    while (bomb_count < this->bombs) {
        int rand_index = rand() % (this->width * this->height);

        int x = rand_index % this->width;
        int y = rand_index / this->width;

        // Do not place bombs in the safe zone
        if (abs(x - safe_x) <= safe_radius && abs(y - safe_y) <= safe_radius) {
            continue;
        }

        struct Square *square = this->get_square(x, y);

        if (!square->is_bomb) {
            square->is_bomb = true;
            bomb_count++;
        }
    }
}

struct Square *Board::get_square(int x, int y) { return &this->board[y][x]; }

void Board::print() const {
    for (auto row : this->board) {
        for (auto square : row) {
            if (square.is_bomb) {
                std::cout << "O ";
            } else {
                std::cout << "X ";
            }
        }
        std::cout << "\n";
    }
}

void Board::calculate_numbers() {
    for (int y = 0; y < this->height; y++) {
        for(int x = 0; x < this->width; x++) {
            struct Square *square = this->get_square(x, y);

            if (!square->is_bomb) {
                continue;
            }

            for (std::pair<int, int> neighbour : get_neighbours(x, y)) {
                struct Square *square = this->get_square(neighbour.first, neighbour.second);
                
                // Don't add the count to bombs
                if (square->is_bomb) {
                    continue;
                }

                square->count++;
            }
        }
    }
}

std::vector<std::pair<int, int>> Board::get_neighbours(int x, int y) const {
    std::vector<std::pair<int, int>> neighbours;

    for (int i = 0; i < 9; i++) {
        int neigh_x = i/3 + x - 1;
        int neigh_y = i%3 + y - 1;

        // Ignore the square itself
        if (neigh_x == x && neigh_y == y) {
            continue;
        }

        // Check the bounds
        if (neigh_x < 0 || neigh_y < 0) {
            continue;
        }
        if (neigh_x >= width || neigh_y >= height) {
            continue;
        }
        
        neighbours.push_back({neigh_x, neigh_y});
    }
    return neighbours;
}
