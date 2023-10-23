#pragma once

#include <string>

#include "board.h"

class Game {
public:
    Game();
    void play();

private:
    Board board_;
    std::string first_turn_;
};
