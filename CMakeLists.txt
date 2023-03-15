cmake_minimum_required(VERSION 3.10)

project(Minesweeper VERSION 1.0)

file(GLOB_RECURSE minesweeper_src CONFIGURE_DEPENDS "src/*.cpp" "src/*.h")

add_executable(Minesweeper ${minesweeper_src})
