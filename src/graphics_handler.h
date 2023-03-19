#ifndef _GRAPHICS_HANDLER
#define _GRAPHICS_HANDLER

#include "renderer.h"
#include <unordered_map>

class GraphicsHandler {
public:
    GraphicsHandler(Board *board, Renderer *renderer);

    void draw() const;
    
private:
    static const int CELL_SIZE = 1;

    static constexpr char HORIZONTAL[] = "─";
    static constexpr char VERTICAL[] = "│";
    static constexpr char VERTICAL_LEFT[] = "├";
    static constexpr char VERTICAL_RIGHT[] = "┤";
    static constexpr char HORIZONTAL_TOP[] = "┬";
    static constexpr char HORIZONTAL_BOTTOM[] = "┴";
    static constexpr char MIDDLE[] = "┼";
    static constexpr char TOP_RIGHT[] = "┐";
    static constexpr char TOP_LEFT[] = "┌";
    static constexpr char BOTTOM_RIGHT[] = "┘";
    static constexpr char BOTTOM_LEFT[] = "└";

    static const int BOARD_MARGIN_X = 10;
    static const int BOARD_MARGIN_Y = 0;

    static const Color BOARD_OUTLINE = white;
    static const Color SELECTION = yellow;

    const std::unordered_map<int, Color> NUMBER_COLOR = {
        {1, blue},
        {2, green},
        {3, red},
        {4, magenta},
        {5, yellow},
        {6, cyan},
        {7, black},
        {8, white}
    };

    Board *board;

    int board_width;
    int board_height;

    int term_width;
    int term_height;

    Renderer* renderer;

    // Set the terminal dimensions
    void set_term_dim();
    std::pair<int, int> abs_to_board(int x, int y) const;

    void draw_box(int x_pos, int y_pos, int width, int height) const;

    void draw_board() const;
    void draw_board_outline() const;
    void draw_board_content() const;

    void draw_to_board(int x, int y, std::string text, Color color) const;
    void draw_board_selection() const;
};

#endif
