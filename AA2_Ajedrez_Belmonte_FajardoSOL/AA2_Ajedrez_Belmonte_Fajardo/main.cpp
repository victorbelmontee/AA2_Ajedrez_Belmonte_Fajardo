#include "Const.h"
#include "Board.h"

int main() {
	char chessBoard[BOARD_SIZE][BOARD_SIZE];

	initBoard(chessBoard);

	printBoard(chessBoard);
}