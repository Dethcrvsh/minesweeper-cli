#ifndef _BOARD
#define _BOARD

#include "renderer.h"
#include <string>
#include <vector>

struct Square {
    bool is_open;
    bool is_bomb;
    bool is_flagged;
    int count;
};

class Board {
public:
    Board(int width, int height, int bombs);

    struct Square *get_square(int x, int);

    void print() const;

    int get_width() const;
    int get_height() const;

    std::pair<int, int>* get_selection();

    // Uncover at the current selection
    void uncover();

    void move_selection(int x, int y);

    // Sets or unsets the flag at the current selection
    void set_flag();

private:
    const int SAFE_RADIUS = 1;

    int width;
    int height;
    int bombs;
    int populated;
    std::vector<std::vector<struct Square>> board;

    std::pair<int, int> selection;

    void init_board();
    void populate_bombs(int safe_x, int safe_y, int safe_radius);

    void calculate_numbers();

    // Uncover all neighbours with no adjacent bombs
    void uncover_empty_neighbours(int x, int y);

    std::vector<std::pair<int, int>> get_neighbours(int x, int y) const;
};

#endif
