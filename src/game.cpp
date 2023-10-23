#include <iostream>
#include <cstdlib>

#include <game.h>

Game::Game() {
    int toss = std::rand();

    if (toss % 2 == 0) {
        first_turn_ = "bot";
        board_.set_bot_turn();
    }
    else
        first_turn_ = "player";
}

void Game::play() {
    while (!board_.is_game_over()) {
        if (first_turn_ == "bot") {
            board_.bot_move();
            board_.player_move();
        } else {
            board_.player_move();
            board_.bot_move();
        }
    }
}
