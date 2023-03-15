#ifndef _RENDERER
#define _RENDERER

#include "board.h"
#include <string>

class Renderer {
public:
    Renderer(int board_width, int board_height, std::ostream *stream);

    ~Renderer();

    // Draws the text to the board coordinates
    void draw_to_board(int x, int y, std::string text) const;

private:
    static const int CELL_SIZE = 1;

    // Ansi escape codes
    static constexpr char ESC[] = "\033";
    static constexpr char CONTROL_SEQ[] = "[";
    static constexpr char COMMAND_DIV[] = ";";

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

    int board_width;
    int board_height;

    std::ostream *stream;

    void ansi_command(std::string &command) const;

    void show_cursor() const;
    void hide_cursor() const;
    void move_cursor(int x, int y) const;
    void reset_cursor() const;
    void clear() const;
    void draw(int x, int y, std::string text) const;

    // Draws a box at the given position
    void draw_box(int x_pos, int y_pos, int width, int height) const;

    void draw_board(int x_pos, int y_pos) const;

    // Translate absolute to board coordinates
    std::pair<int, int> abs_to_board(int x, int y) const;
};

#endif
