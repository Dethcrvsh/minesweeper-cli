#include "renderer.h"
#include <iostream>
#include <stdlib.h>
#include <string>
#include <cstring>
#include <unistd.h>

Renderer::Renderer(std::ostream *stream)
    : stream(stream) {

    this->hide_cursor();
    this->clear();

    // Make sure the buffer is empty
    std::memset(buffer, '\0', sizeof(buffer));
}

Renderer::~Renderer() {
    this->show_cursor();
    this->clear();
    this->reset_cursor();

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

void Renderer::start_color(Color color) {
    current_color = color;

    std::string color_out = "";
    color_out
        .append("1;3")
        .append(std::to_string(color))
        .append("m"); 

    this->ansi_command(color_out);
}

void Renderer::reset_color() {
    current_color = white;

    std::string color_out = "0m";
    this->ansi_command(color_out);
}

void Renderer::draw(int x, int y, std::string text) {
    bool was_added_to_buffer = add_to_buffer(x, y, text);

    if (!was_added_to_buffer) {
	return;
    }

    move_cursor(x, y);
    *stream << text;
    // TODO: Move this
    move_cursor(75, 75);
}

bool Renderer::add_to_buffer(int x, int y, std::string text) {
    // I have no idea why I'm using string everywhere in the code when only
    // one char should be handled. true mongo moment
    char new_char = text.c_str()[0];

    if (!(0 <= x && x < BUFFER_WIDTH && 0 <= y && y < BUFFER_HEIGHT)) {
	return false;
    }

    struct BufferEntry old_entry = buffer[x + y * BUFFER_WIDTH];

    buffer[x + y * BUFFER_WIDTH] = {new_char, current_color};

    return old_entry.text != new_char || old_entry.color != current_color;
}

