#ifndef _RENDERER
#define _RENDERER

#include "board.h"
#include <string>
#include "term_colors.h"

class Renderer {
public:
    Renderer(std::ostream *stream);

    ~Renderer();

    void draw(int x, int y, std::string text) const;
    void clear() const;

    void start_color(Color color) const;
    void reset_color() const;

private:
    // Ansi escape codes
    static constexpr char ESC[] = "\033";
    static constexpr char CONTROL_SEQ[] = "[";
    static constexpr char COMMAND_DIV[] = ";";

    std::ostream *stream;

    void ansi_command(std::string &command) const;

    void show_cursor() const;
    void hide_cursor() const;
    void move_cursor(int x, int y) const;
    void reset_cursor() const;

    // Draws a box at the given position
    void draw_box(int x_pos, int y_pos, int width, int height) const;

    void draw_board(int x_pos, int y_pos) const;

    // Translate absolute to board coordinates
    std::pair<int, int> abs_to_board(int x, int y) const;
};

#endif
