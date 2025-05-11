#pragma once

#include "Const.h"
#include "Utils.h"



// Declaraciones de funciones
void initChessBoard(char chessBoard[BOARD_SIZE][BOARD_SIZE]);
void viewChessBoard(char chessBoard[BOARD_SIZE][BOARD_SIZE]);
void movePieceByUser(char chessBoard[BOARD_SIZE][BOARD_SIZE], bool isWhiteTurn);
bool isValidMove(char chessBoard[BOARD_SIZE][BOARD_SIZE], Position from, Position to, bool isWhiteTurn);
bool hasAnyValidMove(char chessBoard[BOARD_SIZE][BOARD_SIZE], Position from, bool isWhiteTurn);