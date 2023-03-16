#include <unordered_map>

enum Action {
    MOVE_LEFT,
    MOVE_RIGHT,
    MOVE_UP,
    MOVE_DOWN,
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

        {'f', FLAG},

        {'g', UNCOVER}
    };    
};
