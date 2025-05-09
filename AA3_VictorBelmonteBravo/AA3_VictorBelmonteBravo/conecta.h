#ifndef CONECTA_H
#define CONECTA_H

#include <iostream>
#include <vector>

const int MIN_BOARD_SIZE = 3;
const int MAX_BOARD_SIZE = 5;
const char EMPTY = '~';
const char PLAYER_X = 'X';
const char PLAYER_O = 'O';

class Conecta {
public:
    Conecta(int size);
    void play();
private:
    int boardSize;
    std::vector<std::vector<char>> board;
    bool isGameOver();
    void printBoard() const;
    bool checkWin(char player) const;
    bool isValidMove(int col) const;
    void placeToken(int col, char player);
    int getNextPlayer() const;
};

#endif // CONECTA_H
