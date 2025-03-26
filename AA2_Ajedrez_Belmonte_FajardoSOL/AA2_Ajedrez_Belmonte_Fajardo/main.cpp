#include "Const.h"
#include "Board.h"
#include "Utils.h"

int main() {
    char chessBoard[BOARD_SIZE][BOARD_SIZE];
    bool gameOver = false;
    bool isWhiteTurn = true;
    initChessBoard(chessBoard);

    do {
        std::string actualTurn = isWhiteTurn ? "BLANCAS" : "NEGRAS";
        std::cout << " Turno de las: " << actualTurn << std::endl;

        viewChessBoard(chessBoard);

        Position userGetPiece, userSetPiece;

        userGetPiece = getPieceByUser(chessBoard, isWhiteTurn);

        isWhiteTurn = !isWhiteTurn;
        system("cls");

    } while (!gameOver);
}