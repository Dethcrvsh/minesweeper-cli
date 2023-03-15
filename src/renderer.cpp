#include "renderer.h"
#include <iostream>
#include <stdlib.h>
#include <string>
#include <unistd.h>

Renderer::Renderer(std::ostream *stream)
    : stream(stream) {

    this->hide_cursor();
    this->clear();
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

void Renderer::draw(int x, int y, std::string text) const {
    this->move_cursor(x, y);
    *this->stream << text;
}

