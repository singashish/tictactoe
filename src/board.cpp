#include <iostream>
#include <cstdlib>
#include <climits>
#include <ctime>

#include <board.h>

Board::Board() : bot_turn_first_(false) {
    board_ = std::vector<std::string>(9, " ");
}

void Board::player_move() {
    std::cout << "Enter Position: ";
    int pos;
    std::cin >> pos;
    insert(pos - 1, "X");
}

void Board::bot_move() {
    if (bot_turn_first_) {
        bot_turn_first_ = false;
        int move = std::rand() % 9;
        insert(move, "O");
    }
    else {
        int bestScore = INT_MIN;
        int bestMove;

        for (int i = 0; i < 9; i++) {
            if (board_[i] == " ") {
                board_[i] = "O";
                int score = minimax(0, INT_MIN, INT_MAX, false);
                board_[i] = " ";

                if (score > bestScore) {
                    bestScore = score;
                    bestMove = i;
                }
            }
        }

        insert(bestMove, "O");
    }
}

void Board::set_bot_turn() {
    bot_turn_first_ = true;
}

void Board::insert(int pos, const std::string& key) {
    if (pos < 0 || pos >= 9) {
        std::cout << pos << ": Invalid position. Please enter a position between 1 and 9." << std::endl;
        std::cout << "Enter Position: ";
        int newPos;
        std::cin >> newPos;
        insert(newPos - 1, key);
        return; // Return to prevent further execution in this case.
    }

    if (board_[pos] == " ") {
        board_[pos] = key;
        clrscr();
        print_board();

        if (win()) {
            if (key == "O")
                std::cout << "BOT WINS" << "\n";
            else
                std::cout << "YOU WIN" << "\n";
            exit(0);
        }
        else if (draw()) {
            std::cout << "GAME DRAW" << "\n";
            exit(0);
        }

    }
    else {
        std::cout << "Not Available, choose another cell." << "\n" << "Enter Position: ";
        int newPos;
        std::cin >> newPos;
        insert(newPos - 1, key);
    }

    return;
}

void Board::clrscr() {
    std::cout << "\033[2J\033[1;1H";
}

bool Board::win() const {
    if (board_[0] == board_[1] && board_[0] == board_[2] && board_[0] != " ")
        return true;
    else if (board_[3] == board_[4] && board_[3] == board_[5] && board_[3] != " ")
        return true;
    else if (board_[6] == board_[7] && board_[6] == board_[8] && board_[6] != " ")
        return true;
    else if (board_[0] == board_[3] && board_[0] == board_[6] && board_[0] != " ")
        return true;
    else if (board_[1] == board_[4] && board_[1] == board_[7] && board_[1] != " ")
        return true;
    else if (board_[2] == board_[5] && board_[2] == board_[8] && board_[2] != " ")
        return true;
    else if (board_[0] == board_[4] && board_[0] == board_[8] && board_[0] != " ")
        return true;
    else if (board_[6] == board_[4] && board_[6] == board_[2] && board_[6] != " ")
        return true;

    return false;
}

bool Board::who_won(const std::string& key) const {
    if (board_[0] == board_[1] && board_[0] == board_[2] && board_[0] == key)
        return true;
    else if (board_[3] == board_[4] && board_[3] == board_[5] && board_[3] == key)
        return true;
    else if (board_[6] == board_[7] && board_[6] == board_[8] && board_[6] == key)
        return true;
    else if (board_[0] == board_[3] && board_[0] == board_[6] && board_[0] == key)
        return true;
    else if (board_[1] == board_[4] && board_[1] == board_[7] && board_[1] == key)
        return true;
    else if (board_[2] == board_[5] && board_[2] == board_[8] && board_[2] == key)
        return true;
    else if (board_[0] == board_[4] && board_[0] == board_[8] && board_[0] == key)
        return true;
    else if (board_[6] == board_[4] && board_[6] == board_[2] && board_[6] == key)
        return true;

    return false;
}

bool Board::draw() const {
    for (const auto& cell : board_) {
        if (cell == " ")
            return false;
    }
    return true;
}

void Board::print_board() const {
    std::cout << " " << board_[0] << " |" << " " << board_[1] << " |" << " " << board_[2] << "\n";
    std::cout << "---+---+---" << "\n";
    std::cout << " " << board_[3] << " |" << " " << board_[4] << " |" << " " << board_[5] << "\n";
    std::cout << "---+---+---" << "\n";
    std::cout << " " << board_[6] << " |" << " " << board_[7] << " |" << " " << board_[8] << "\n";
    std::cout << "\n";
}

bool Board::is_game_over() const {
    // return win() || draw();
    return win();
}

int Board::minimax(int depth, int alpha, int beta, bool isMax) {
    if (who_won("O"))
        return 10;
    else if (who_won("X"))
        return -10;
    else if (draw())
        return 0;

    int bestScore;

    if (isMax) {
        bestScore = INT_MIN;

        for (int i = 0; i < 9; i++) {
            if (board_[i] == " ") {
                board_[i] = "O";
                int score = minimax(depth + 1, alpha, beta, false);
                board_[i] = " ";
                bestScore = std::max(bestScore, score - depth);
                alpha = std::max(alpha, score);

                if (beta <= alpha)
                    break;
            }
        }
    } else {
        bestScore = INT_MAX;

        for (int i = 0; i < 9; i++) {
            if (board_[i] == " ") {
                board_[i] = "X";
                int score = minimax(depth + 1, alpha, beta, true);
                board_[i] = " ";
                bestScore = std::min(bestScore, score + depth);
                beta = std::min(beta, score);

                if (beta <= alpha)
                    break;
            }
        }
    }

    return bestScore;
}
