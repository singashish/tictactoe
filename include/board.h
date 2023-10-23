#pragma once

#include <vector>

class Board {
public:
    Board();
    void player_move();
    void bot_move();
    void set_bot_turn();
    void print_board() const;
    bool is_game_over() const;

private:
    void insert(int pos, const std::string& key);
    void clrscr();
    bool win() const;
    bool draw() const;
    bool who_won(const std::string& key) const;
    int minimax(int depth, int alpha, int beta, bool isMax);

    std::vector<std::string> board_;
    bool bot_turn_first_;
};
