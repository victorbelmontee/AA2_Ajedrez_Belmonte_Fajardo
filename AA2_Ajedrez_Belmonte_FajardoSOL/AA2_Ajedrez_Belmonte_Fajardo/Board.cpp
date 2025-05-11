#include "Board.h"
#include <iostream>

// Inicializa el tablero de ajedrez
void initChessBoard(char chessBoard[BOARD_SIZE][BOARD_SIZE]) {
    for (int i = 0; i < BOARD_SIZE; i++) {
        for (int j = 0; j < BOARD_SIZE; j++) {
            // Colocar peones
            if (j == BOARD_SIZE - 2) {
                chessBoard[j][i] = WHITE_PAWN;
            }
            else if (j == 1) {
                chessBoard[j][i] = BLACK_PAWN;
            }
            else {
                chessBoard[j][i] = EMPTY; // Espacios vacíos
            }
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

// Verifica si una pieza tiene al menos un movimiento válido
bool hasAnyValidMove(char chessBoard[BOARD_SIZE][BOARD_SIZE], Position from, bool isWhiteTurn) {
    for (int y = 0; y < BOARD_SIZE; y++) {
        for (int x = 0; x < BOARD_SIZE; x++) {
            Position to = { x, y };
            if (isValidMove(chessBoard, from, to, isWhiteTurn)) {
                return true;
            }
        }
    }
    return false;
}

// Verifica si el movimiento es válido
bool isValidMove(char chessBoard[BOARD_SIZE][BOARD_SIZE], Position from, Position to, bool isWhiteTurn) {
    char piece = chessBoard[from.y][from.x];
    char target = chessBoard[to.y][to.x];
   

    int difx = to.x - from.x;
    int dify = to.y - from.y;
    if (piece == WHITE_QUEEN || piece == BLACK_QUEEN) {
        // La reina se mueve como una torre O como un alfil
        // Comprobar movimiento de torre (horizontal o vertical)
        if (difx == 0 || dify == 0) {
            // Código para validar el movimiento como torre
            if (difx == 0) {
                int step = 1;
                if (dify < 0) {
                    step = -1;
                }
                for (int y = from.y + step; y != to.y; y += step) {
                    if (chessBoard[y][from.x] != EMPTY) {
                        return false;
                    }
                }
                return true;
            }
            if (dify == 0) {
                int step = 1;
                if (difx < 0) {
                    step = -1;
                }
                for (int x = from.x + step; x != to.x; x += step) {
                    if (chessBoard[from.y][x] != EMPTY) {
                        return false;
                    }
                }
                return true;
            }
        }
        
        // Comprobar movimiento de alfil (diagonal)
        if (difx == dify || difx == -dify) {
            int stepX = 1;
            int stepY = 1;
            if (difx < 0) {
                stepX = -1;
            }
            if (dify < 0) {
                stepY = -1;
            }
            int x = from.x + stepX;
            int y = from.y + stepY;
            while (x != to.x && y != to.y) {
                if (chessBoard[y][x] != EMPTY) {
                    return false;
                }
                x += stepX;
                y += stepY;
            }
            return true;
        }
        
        return false;
    }
    if (isWhiteTurn) {
        if (target >= 'A' && target <= 'Z') {
            return false;
        }
    }
    else {
        if (target >= 'a' && target <= 'z') {
            if (piece == WHITE_QUEEN || piece == BLACK_QUEEN) {
                // La reina se mueve como una torre O como un alfil
                // Comprobar movimiento de torre (horizontal o vertical)
                if (difx == 0 || dify == 0) {
                    // Código de validación de torre
                    if (difx == 0) {
                        int step = 1;
                        if (dify < 0) {
                            step = -1;
                        }
                        for (int y = from.y + step; y != to.y; y += step) {
                            if (chessBoard[y][from.x] != EMPTY) {
                                return false;
                            }
                        }
                        return true;
                    }
                    if (dify == 0) {
                        int step = 1;
                        if (difx < 0) {
                            step = -1;
                        }
                        for (int x = from.x + step; x != to.x; x += step) {
                            if (chessBoard[from.y][x] != EMPTY) {
                                return false;
                            }
                        }
                        return true;
                    }
                }
                
                // Comprobar movimiento de alfil (diagonal)
                if (difx == dify || difx == -dify) {
                    int stepX = 1;
                    int stepY = 1;
                    if (difx < 0) {
                        stepX = -1;
                    }
                    if (dify < 0) {
                        stepY = -1;
                    }
                    int x = from.x + stepX;
                    int y = from.y + stepY;
                    while (x != to.x && y != to.y) {
                        if (chessBoard[y][x] != EMPTY) {
                            return false;
                        }
                        x += stepX;
                        y += stepY;
                    }
                    return true;
                }
                return false;
            }
            return false;
        }
    }


    if (piece == WHITE_PAWN || piece == BLACK_PAWN) {
        int direction = 1;
        int startRow = 1;

        if (piece == WHITE_PAWN) {
            direction = -1;
            startRow = BOARD_SIZE - 2;
        }

        if (difx == 0 && dify == direction && target == EMPTY) {
            return true;
        }
        if (difx == 0 && dify == 2 * direction && from.y == startRow && chessBoard[from.y + direction][from.x] == EMPTY && target == EMPTY) {
            return true;
        }
        if ((difx == 1 || difx == -1) && dify == direction && target != EMPTY) {
            return true;
        }

        return false;
    }

    if (piece == WHITE_ROOK || piece == BLACK_ROOK) {
        if (difx == 0) {
            int step = 1;
            if (dify < 0) {
                step = -1;
            }
            for (int y = from.y + step; y != to.y; y += step) {
                if (chessBoard[y][from.x] != EMPTY) {
                    return false;
                }
            }
            return true;
        }
        if (dify == 0) {
            int step = 1;
            if (difx < 0) {
                step = -1;
            }
            for (int x = from.x + step; x != to.x; x += step) {
                if (chessBoard[from.y][x] != EMPTY) {
                    return false;
                }
            }
            return true;
        }
        return false;
    }

    if (piece == WHITE_KNIGHT || piece == BLACK_KNIGHT) {
        if ((difx == 2 && dify == 1) || (difx == 2 && dify == -1) ||
            (difx == -2 && dify == 1) || (difx == -2 && dify == -1) ||
            (difx == 1 && dify == 2) || (difx == 1 && dify == -2) ||
            (difx == -1 && dify == 2) || (difx == -1 && dify == -2)) {
            return true;
        }
        return false;
    }

    if (piece == WHITE_BISHOP || piece == BLACK_BISHOP) {
        if (difx == dify || difx == -dify) {
            int stepX = 1;
            int stepY = 1;
            if (difx < 0) {
                stepX = -1;
            }
            if (dify < 0) {
                stepY = -1;
            }
            int x = from.x + stepX;
            int y = from.y + stepY;
            while (x != to.x && y != to.y) {
                if (chessBoard[y][x] != EMPTY) {
                    return false;
                }
                x += stepX;
                y += stepY;
            }
            return true;
        }
        return false;
    }

    if (piece == WHITE_QUEEN || piece == BLACK_QUEEN) {
        if (isValidMove(chessBoard, from, to, isWhiteTurn)) {
            return true;
        }
        return false;
    }

    if (piece == WHITE_KING || piece == BLACK_KING) {
        if ((difx >= -1 && difx <= 1) && (dify >= -1 && dify <= 1)) {
            return true;
        }
        return false;
    }

    return false;
}

// Verifica si un rey sigue vivo
bool isKingAlive(char chessBoard[BOARD_SIZE][BOARD_SIZE], char king) {
    for (int y = 0; y < BOARD_SIZE; y++) {
        for (int x = 0; x < BOARD_SIZE; x++) {
            if (chessBoard[y][x] == king) {
                return true;
            }
        }
    }
    return false;
}

// Permite al usuario seleccionar una pieza válida y moverla
void movePieceByUser(char chessBoard[BOARD_SIZE][BOARD_SIZE], bool isWhiteTurn) {
    Position from, to;
    bool isValidSelection = false;
    bool isValidDestination = false;

    // Seleccionar pieza válida
    do {
        std::cout << "------------------" << std::endl;
        if (isWhiteTurn) {
            std::cout << "Turno de las BLANCAS" << std::endl;
        }
        else {
            std::cout << "Turno de las NEGRAS" << std::endl;
        }
        std::cout << "Elige una pieza (X Y): ";
        std::cin >> from.x >> from.y;
        std::cout << "------------------" << std::endl;

        if (from.x < 1 || from.x > BOARD_SIZE || from.y < 1 || from.y > BOARD_SIZE) {
            std::cout << "Posicion fuera del tablero. Intenta de nuevo." << std::endl;
            continue;
        }

        from.x--;
        from.y = BOARD_SIZE - from.y;

        char selectedPiece = chessBoard[from.y][from.x];

        if (selectedPiece == EMPTY) {
            std::cout << "No hay ninguna pieza en esa posicion." << std::endl;
        }
        else if (isWhiteTurn && (selectedPiece < 'A' || selectedPiece > 'Z')) {
            std::cout << "Esa pieza no te pertenece." << std::endl;
        }
        else if (!isWhiteTurn && (selectedPiece < 'a' || selectedPiece > 'z')) {
            std::cout << "Esa pieza no te pertenece." << std::endl;
        }
        else if (!hasAnyValidMove(chessBoard, from, isWhiteTurn)) {
            std::cout << "Esa pieza no tiene movimientos validos. Elige otra." << std::endl;
        }
        else {
            isValidSelection = true;
        }
    } while (!isValidSelection);

    // Seleccionar destino
    do {
        std::cout << "Elige la posicion de destino (X Y): ";
        std::cin >> to.x >> to.y;

        if (to.x < 1 || to.x > BOARD_SIZE || to.y < 1 || to.y > BOARD_SIZE) {
            std::cout << "Posicion fuera del tablero. Intenta de nuevo." << std::endl;
            continue;
        }

        to.x--;
        to.y = BOARD_SIZE - to.y;

        if (isValidMove(chessBoard, from, to, isWhiteTurn)) {
            isValidDestination = true;
        }
        else {
            std::cout << "Movimiento no valido. Intenta de nuevo." << std::endl;
        }
    } while (!isValidDestination);

    // Mover pieza
    char piece = chessBoard[from.y][from.x];
    chessBoard[from.y][from.x] = EMPTY;
    chessBoard[to.y][to.x] = piece;

    // Verificar si el rey enemigo ha sido eliminado
    if (isWhiteTurn) {
        if (!isKingAlive(chessBoard, BLACK_KING)) {
            std::cout << "¡Las BLANCAS han ganado! El rey negro ha sido eliminado." << std::endl;
            exit(0); // Termina el programa
        }
    }
    else {
        if (!isKingAlive(chessBoard, WHITE_KING)) {
            std::cout << "¡Las NEGRAS han ganado! El rey blanco ha sido eliminado." << std::endl;
            exit(0); // Termina el programa
        }
    }
}
