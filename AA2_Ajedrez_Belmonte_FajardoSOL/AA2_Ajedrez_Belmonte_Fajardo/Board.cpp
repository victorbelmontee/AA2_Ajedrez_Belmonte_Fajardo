#include "Const.h"
#include "Utils.h"

void initBoard(char chessBoard[BOARD_SIZE][BOARD_SIZE]) {
    for (int i = 0; i < BOARD_SIZE; i++) {
        for (int j = 0; j < BOARD_SIZE; j++) {
            // Set paws
            if (j == BOARD_SIZE - 2) chessBoard[j][i] = BLACK_PAWN;
            else if (j == 1) chessBoard[j][i] = WHITE_PAWN;
            else chessBoard[j][i] = EMPTY; // Set empty spaces
        }
    }

    const short rookXPosL = 0;
    const short rookXPosR = BOARD_SIZE - 1;
    const short knightXPosL = 1;
    const short knightXPosR = BOARD_SIZE - 2;
    const short bishopXPosL = 2;
    const short bishopXPosR = BOARD_SIZE - 3;

    const short whiteKingXPosL = 3;
    const short whiteQueenXPosR = BOARD_SIZE - 4;
    const short blackKingXPosL = BOARD_SIZE - 4;
    const short blackQueenXPosR = 3;

    // Set black chess pieces
    chessBoard[0][rookXPosL] = BLACK_ROOK;
    chessBoard[0][rookXPosR] = BLACK_ROOK;
    chessBoard[0][knightXPosL] = BLACK_KNIGHT;
    chessBoard[0][knightXPosR] = BLACK_KNIGHT;
    chessBoard[0][bishopXPosL] = BLACK_BISHOP;
    chessBoard[0][bishopXPosR] = BLACK_BISHOP;
    chessBoard[0][whiteKingXPosL] = BLACK_KING;
    chessBoard[0][whiteQueenXPosR] = BLACK_QUEEN;

    // Set white chess pieces
    chessBoard[BOARD_SIZE - 1][rookXPosL] = WHITE_ROOK;
    chessBoard[BOARD_SIZE - 1][rookXPosR] = WHITE_ROOK;
    chessBoard[BOARD_SIZE - 1][knightXPosL] = WHITE_KNIGHT;
    chessBoard[BOARD_SIZE - 1][knightXPosR] = WHITE_KNIGHT;
    chessBoard[BOARD_SIZE - 1][bishopXPosL] = WHITE_BISHOP;
    chessBoard[BOARD_SIZE - 1][bishopXPosR] = WHITE_BISHOP;
    chessBoard[BOARD_SIZE - 1][blackKingXPosL] = WHITE_KING;
    chessBoard[BOARD_SIZE - 1][blackQueenXPosR] = WHITE_QUEEN;
}

void printBoard(char chessBoard[BOARD_SIZE][BOARD_SIZE]) {
    std::cout << ' ' << ' ';
    for (int i = 0; i < BOARD_SIZE; i++) {
        std::cout << i + 1 << ' ';
    }
    std::cout << std::endl;

    for (int i = 0; i < BOARD_SIZE; i++) {
        std::cout << BOARD_SIZE - i << ' ';
        for (int j = 0; j < BOARD_SIZE; j++) {
            std::cout << chessBoard[i][j] << ' ';
        }
        std::cout << std::endl;
    }
}

Position getPieceByUser(char chessBoard[BOARD_SIZE][BOARD_SIZE], bool isWhiteTurn) {
    Position userGetPiece;
    bool isGettingAPiece = true;
    do {
        isGettingAPiece = true;
        std::cout << "------------------" << std::endl;
        std::cout << " Elige una pieza: " << std::endl;
        std::cout << " X: ";
        std::cin >> userGetPiece.x;

        std::cout << " Y: ";
        std::cin >> userGetPiece.y;

        if (userGetPiece.x < 1 || userGetPiece.x > BOARD_SIZE ||
            userGetPiece.y < 1 || userGetPiece.y > BOARD_SIZE) {
            std::cout << "INPUT INVALIDO" << std::endl;
        }
        else {
            if (isWhiteTurn) {
            }
        }
    } while (!isGettingAPiece);

    userGetPiece.x--;
    userGetPiece.y--;

    userGetPiece.y = BOARD_SIZE - userGetPiece.y;

    return userGetPiece;
}

void setPieceByUser() {
}