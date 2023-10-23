#include <ctime>
#include <game.h>

int main() {
    std::srand(static_cast<unsigned int>(std::time(0)));

    Game game;
    game.play();

    return 0;
}
