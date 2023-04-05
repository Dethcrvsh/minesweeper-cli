#include <unordered_map>

enum Action {
    MOVE_LEFT,
    MOVE_RIGHT,
    MOVE_UP,
    MOVE_DOWN,
    MOVE_MODIFIER,
    FLAG,
    UNCOVER
};

struct Keybinds {
    std::unordered_map<char, Action> keybinds = {
        {'h', MOVE_LEFT},
        {'a', MOVE_LEFT},
        {37, MOVE_LEFT},

        {'l', MOVE_RIGHT},
        {'d', MOVE_RIGHT},
        {39, MOVE_RIGHT},

        {'k', MOVE_UP},
        {'w', MOVE_UP},
        {38, MOVE_UP},

        {'j', MOVE_DOWN},
        {'s', MOVE_DOWN},
        {40, MOVE_DOWN},

        {1, MOVE_MODIFIER},
        {2, MOVE_MODIFIER},
        {3, MOVE_MODIFIER},
        {4, MOVE_MODIFIER},
        {5, MOVE_MODIFIER},
        {6, MOVE_MODIFIER},
        {7, MOVE_MODIFIER},
        {8, MOVE_MODIFIER},
        {9, MOVE_MODIFIER},

        {'f', FLAG},

        {'g', UNCOVER}
    };    
};
