#include "conecta.h"

Conecta::Conecta(int size) : boardSize(size), board(size, std::vector<char>(size, EMPTY)) {}

void Conecta::play() {
    int player = 1; // Player X starts
    while (true) {
        printBoard();
        int col;
        std::cout << "Player " << (player == 1 ? 'X' : 'O') << ", enter column to place your token: ";
        std::cin >> col;
        if (col < 1 || col > boardSize) {
            std::cout << "Invalid column. Please try again.\n";
            continue;
        }
        if (!isValidMove(col - 1)) {
            std::cout << "Column full. Please try again.\n";
            continue;
        }
        placeToken(col - 1, player == 1 ? PLAYER_X : PLAYER_O);
        if (checkWin(player == 1 ? PLAYER_X : PLAYER_O)) {
            printBoard();
            std::cout << "Player " << (player == 1 ? 'X' : 'O') << " wins!\n";
            break;
        }
        if (isGameOver()) {
            printBoard();
            std::cout << "Game over. No more moves.\n";
            break;
        }
        player = getNextPlayer();
    }
}

bool Conecta::isGameOver() const {
    for (int i = 0; i < boardSize; ++i) {
        if (board[0][i] == EMPTY) return false;
    }
    return true;
}

void Conecta::printBoard() const {
    for (int i = 0; i < boardSize; ++i) {
        for (int j = 0; j < boardSize; ++j) {
            std::cout << board[i][j] << " ";
        }
        std::cout << "\n";
    }
}

bool Conecta::checkWin(char player) const {
    // Check horizontal, vertical, and diagonal for a win
    for (int i = 0; i < boardSize; ++i) {
        for (int j = 0; j <= boardSize - MIN_BOARD_SIZE; ++j) {
            if ((board[i][j] == player && board[i][j + 1] == player && board[i][j + 2] == player && board[i][j + 3] == player) ||
                (board[j][i] == player && board[j + 1][i] == player && board[j + 2][i] == player && board[j + 3][i] == player)) {
                return true;
            }
        }
    }
    for (int i = 0; i <= boardSize - MIN_BOARD_SIZE; ++i) {
        for (int j = 0; j <= boardSize - MIN_BOARD_SIZE; ++j) {
            if ((board[i][j] == player && board[i + 1][j + 1] == player && board[i + 2][j + 2] == player && board[i + 3][j + 3] == player) ||
                (board[i][boardSize - j - 1] == player && board[i + 1][boardSize - j - 2] == player && board[i + 2][boardSize - j - 3] == player && board[i + 3][boardSize - j - 4] == player)) {
                return true;
            }
        }
    }
    return false;
}

bool Conecta::isValidMove(int col) const {
    return board[0][col] == EMPTY;
}

void Conecta::placeToken(int col, char player) {
    for (int i = boardSize - 1; i >= 0; --i) {
        if (board[i][col] == EMPTY) {
            board[i][col] = player;
            break;
        }
    }
}

int Conecta::getNextPlayer() const {
    return 3 - getNextPlayer(); // Player X starts, so switch between 1 and 2
}
