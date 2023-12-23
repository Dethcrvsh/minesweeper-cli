#ifndef _RENDERER
#define _RENDERER

#include "board.h"
#include <string>
#include "term_colors.h"

class Renderer {
public:
    Renderer(std::ostream *stream);

    ~Renderer();

    void draw(int x, int y, std::string text);
    void clear() const;

    void start_color(Color color);
    void reset_color();

private:
    struct BufferEntry {
        char text;
	Color color;	
    };

    static const int BUFFER_WIDTH = 400;
    static const int BUFFER_HEIGHT = 100;

    // Ansi escape codes
    static constexpr char ESC[] = "\033";
    static constexpr char CONTROL_SEQ[] = "[";
    static constexpr char COMMAND_DIV[] = ";";

    struct BufferEntry buffer[BUFFER_WIDTH * BUFFER_HEIGHT];
    Color current_color;

    std::ostream *stream;

    void ansi_command(std::string &command) const;

    void show_cursor() const;
    void hide_cursor() const;
    void move_cursor(int x, int y) const;
    void reset_cursor() const;

    bool add_to_buffer(int x, int y, std::string text);

    // Translate absolute to board coordinates
    std::pair<int, int> abs_to_board(int x, int y) const;
};

#endif
