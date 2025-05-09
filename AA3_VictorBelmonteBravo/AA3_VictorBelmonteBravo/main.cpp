#include "conecta.h"

int main() {
    int boardSize;
    std::cout << "Select difficulty (3 for easy, 4 for medium, 5 for hard): ";
    std::cin >> boardSize;
    if (boardSize < MIN_BOARD_SIZE || boardSize > MAX_BOARD_SIZE) {
        std::cout << "Invalid difficulty. Exiting.\n";
        return 1;
    }
    Conecta game(boardSize);
    game.play();
    return 0;
}
