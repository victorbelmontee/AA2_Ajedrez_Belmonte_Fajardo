#include "Const.h"
#include "Board.h"
#include "Utils.h"
#include <iostream>

int main() {
    char chessBoard[BOARD_SIZE][BOARD_SIZE];
    bool gameOver = false;
    bool isWhiteTurn = true;

    // Inicializar el tablero
    initChessBoard(chessBoard);

    do {
        // Mostrar el turno actual
        std::string actualTurn = isWhiteTurn ? "BLANCAS" : "NEGRAS";
        std::cout << " Turno de las: " << actualTurn << std::endl;

        // Mostrar el tablero
        viewChessBoard(chessBoard);

        // Mover una pieza
        movePieceByUser(chessBoard, isWhiteTurn);

        // Cambiar de turno
        isWhiteTurn = !isWhiteTurn;

        // Limpiar la pantalla (opcional, solo en Windows)
        system("cls");

    } while (!gameOver);

    return 0;
}
