#include "Board.h"
#include <iostream>

// Inicializa el tablero de ajedrez
void initChessBoard(char chessBoard[BOARD_SIZE][BOARD_SIZE]) {
    for (int i = 0; i < BOARD_SIZE; i++) {
        for (int j = 0; j < BOARD_SIZE; j++) {
            // Colocar peones
            if (j == BOARD_SIZE - 2) chessBoard[j][i] = WHITE_PAWN;
            else if (j == 1) chessBoard[j][i] = BLACK_PAWN;
            else chessBoard[j][i] = EMPTY; // Espacios vacíos
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

    // Colocar piezas negras
    chessBoard[0][rookXPosL] = BLACK_ROOK;
    chessBoard[0][rookXPosR] = BLACK_ROOK;
    chessBoard[0][knightXPosL] = BLACK_KNIGHT;
    chessBoard[0][knightXPosR] = BLACK_KNIGHT;
    chessBoard[0][bishopXPosL] = BLACK_BISHOP;
    chessBoard[0][bishopXPosR] = BLACK_BISHOP;
    chessBoard[0][whiteKingXPosL] = BLACK_KING;
    chessBoard[0][whiteQueenXPosR] = BLACK_QUEEN;

    // Colocar piezas blancas
    chessBoard[BOARD_SIZE - 1][rookXPosL] = WHITE_ROOK;
    chessBoard[BOARD_SIZE - 1][rookXPosR] = WHITE_ROOK;
    chessBoard[BOARD_SIZE - 1][knightXPosL] = WHITE_KNIGHT;
    chessBoard[BOARD_SIZE - 1][knightXPosR] = WHITE_KNIGHT;
    chessBoard[BOARD_SIZE - 1][bishopXPosL] = WHITE_BISHOP;
    chessBoard[BOARD_SIZE - 1][bishopXPosR] = WHITE_BISHOP;
    chessBoard[BOARD_SIZE - 1][blackKingXPosL] = WHITE_KING;
    chessBoard[BOARD_SIZE - 1][blackQueenXPosR] = WHITE_QUEEN;
}

// Muestra el tablero de ajedrez
void viewChessBoard(char chessBoard[BOARD_SIZE][BOARD_SIZE]) {
    std::cout << "  ";
    for (int i = 0; i < BOARD_SIZE; i++) {
        std::cout << i + 1 << ' ';
    }
    std::cout << '\n';

    for (int i = 0; i < BOARD_SIZE; i++) {
        std::cout << BOARD_SIZE - i << ' ';
        for (int j = 0; j < BOARD_SIZE; j++) {
            std::cout << chessBoard[i][j] << ' ';
        }
        std::cout << '\n';
    }
}

// Permite al usuario seleccionar una pieza válida y moverla
void movePieceByUser(char chessBoard[BOARD_SIZE][BOARD_SIZE], bool isWhiteTurn) {
    Position from, to;
    bool isValidMove = false;

    // Seleccionar una pieza válida
    do {
        std::cout << "------------------" << std::endl;
        std::cout << " Elige una pieza: " << std::endl;
        std::cout << " X: ";
        std::cin >> from.x;

        std::cout << " Y: ";
        std::cin >> from.y;

        if (from.x < 1 || from.x > BOARD_SIZE || from.y < 1 || from.y > BOARD_SIZE) {
            std::cout << "INPUT INVALIDO" << std::endl;
            continue;
        }

        // Ajustar coordenadas para el índice del array
        from.x--;
        from.y = BOARD_SIZE - from.y;

        char selectedPiece = chessBoard[from.y][from.x];

        // Verificar si la posición está vacía o si la pieza no pertenece al jugador actual
        if (selectedPiece == EMPTY) {
            std::cout << "No hay ninguna pieza en esa posicion." << std::endl;
        } else if (isWhiteTurn && (selectedPiece < 'A' || selectedPiece > 'Z')) {
            std::cout << "Esa pieza no te pertenece." << std::endl;
        } else if (!isWhiteTurn && (selectedPiece < 'a' || selectedPiece > 'z')) {
            std::cout << "Esa pieza no te pertenece." << std::endl;
        } else {
            isValidMove = true;
        }
    } while (!isValidMove);

    // Seleccionar la posición de destino
    isValidMove = false;
    do {
        std::cout << "------------------" << std::endl;
        std::cout << " Elige la posicion de destino: " << std::endl;
        std::cout << " X: ";
        std::cin >> to.x;

        std::cout << " Y: ";
        std::cin >> to.y;

        if (to.x < 1 || to.x > BOARD_SIZE || to.y < 1 || to.y > BOARD_SIZE) {
            std::cout << "INPUT INVALIDO" << std::endl;
            continue;
        }

        // Ajustar coordenadas para el índice del array
        to.x--;
        to.y = BOARD_SIZE - to.y;

        // Validar que el destino no contenga una pieza del mismo jugador
        char destinationPiece = chessBoard[to.y][to.x];
        if ((isWhiteTurn && destinationPiece >= 'A' && destinationPiece <= 'Z') ||
            (!isWhiteTurn && destinationPiece >= 'a' && destinationPiece <= 'z')) {
            std::cout << "No puedes mover a una posicion ocupada por tu propia pieza." << std::endl;
        } else {
            isValidMove = true;
        }
    } while (!isValidMove);

    // Mover la pieza
    char piece = chessBoard[from.y][from.x];
    chessBoard[from.y][from.x] = EMPTY; // Vaciar la posición original
    chessBoard[to.y][to.x] = piece;    // Mover la pieza a la nueva posición
}
