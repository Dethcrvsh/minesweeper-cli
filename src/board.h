#ifndef _BOARD
#define _BOARD

#include "renderer.h"
#include <string>
#include <vector>

struct Square {
    bool is_open;
    bool is_bomb;
    int count;
};

class Board {
public:
    Board(int width, int height, int bombs);

    struct Square *get_square(int x, int);

    void print() const;

private:
    int width;
    int height;
    int bombs;
    std::vector<std::vector<struct Square>> board;

    static constexpr char HORIZONTAL[] = "─";

    void init_board();
    void populate_bombs();

    void calculate_numbers();

    std::vector<std::pair<int, int>> get_neighbours(int x, int y) const;
};

#endif
