#include "Board.h"
#include <iostream>

// Inicializa el tablero de ajedrez
void initChessBoard(char chessBoard[BOARD_SIZE][BOARD_SIZE]) {
    // Llenamos todo el tablero, 8x8 casillas 
    for (int i = 0; i < BOARD_SIZE; i++) {
        for (int j = 0; j < BOARD_SIZE; j++) {
            if (j == BOARD_SIZE - 2) {
                chessBoard[j][i] = WHITE_PAWN; // Peones blancos en la penúltima fila
            }
            else if (j == 1) {
                chessBoard[j][i] = BLACK_PAWN; // Peones negros en la segunda fila
            }
            else {
                chessBoard[j][i] = EMPTY; //casillas vacías por ahora
            }
        }
    }

    // Constantes para las piezas
    const short rookXPosL = 0;                // Torre izquierda
    const short rookXPosR = BOARD_SIZE - 1;   // Torre derecha
    const short knightXPosL = 1;              // Caballo izquierdo
    const short knightXPosR = BOARD_SIZE - 2; // Caballo derecho
    const short bishopXPosL = 2;              // Alfil izquierdo
    const short bishopXPosR = BOARD_SIZE - 3; // Alfil derecho

    const short whiteKingXPosL = 3;            // Rey blanco 
    const short whiteQueenXPosR = BOARD_SIZE - 4; // Reina blanca
    const short blackKingXPosL = BOARD_SIZE - 4; // Rey negro
    const short blackQueenXPosR = 3;           // Reina negra

    // Colocamos todas las piezas negras en la primera fila
    chessBoard[0][rookXPosL] = BLACK_ROOK;     // Torre negra izquierda
    chessBoard[0][rookXPosR] = BLACK_ROOK;     // Torre negra derecha
    chessBoard[0][knightXPosL] = BLACK_KNIGHT; // Caballo negro izquierdo
    chessBoard[0][knightXPosR] = BLACK_KNIGHT; // Caballo negro derecho
    chessBoard[0][bishopXPosL] = BLACK_BISHOP; // Alfil negro izquierdo
    chessBoard[0][bishopXPosR] = BLACK_BISHOP; // Alfil negro derecho
    chessBoard[0][whiteKingXPosL] = BLACK_KING;   // Rey negro
    chessBoard[0][whiteQueenXPosR] = BLACK_QUEEN; // Reina negra

    // Colocamos todas las piezas blancas en la última fila
    chessBoard[BOARD_SIZE - 1][rookXPosL] = WHITE_ROOK;     // Torre blanca izquierda
    chessBoard[BOARD_SIZE - 1][rookXPosR] = WHITE_ROOK;     // Torre blanca derecha
    chessBoard[BOARD_SIZE - 1][knightXPosL] = WHITE_KNIGHT; // Caballo blanco izquierdo
    chessBoard[BOARD_SIZE - 1][knightXPosR] = WHITE_KNIGHT; // Caballo blanco derecho
    chessBoard[BOARD_SIZE - 1][bishopXPosL] = WHITE_BISHOP; // Alfil blanco izquierdo
    chessBoard[BOARD_SIZE - 1][bishopXPosR] = WHITE_BISHOP; // Alfil blanco derecho
    chessBoard[BOARD_SIZE - 1][blackKingXPosL] = WHITE_KING;   // Rey blanco
    chessBoard[BOARD_SIZE - 1][blackQueenXPosR] = WHITE_QUEEN; // Reina blanca
}

// Muestra el tablero de ajedrez 
void viewChessBoard(char chessBoard[BOARD_SIZE][BOARD_SIZE]) {
    
    std::cout << "  ";
    for (int i = 0; i < BOARD_SIZE; i++) {
        std::cout << i + 1 << ' '; // Numeramos del 1 al 8
    }
    std::cout << '\n';

    for (int i = 0; i < BOARD_SIZE; i++) {
        // Las filas van al revés: 8, 7, 6... 
        std::cout << BOARD_SIZE - i << ' ';
        for (int j = 0; j < BOARD_SIZE; j++) {
            std::cout << chessBoard[i][j] << ' '; // Imprimir la pieza o espacio vacío
        }
        std::cout << '\n';
    }
}

// Verifica si una pieza tiene al menos un movimiento válido

bool hasAnyValidMove(char chessBoard[BOARD_SIZE][BOARD_SIZE], Position from, bool isWhiteTurn) {
    // Probamos todos los destinos posibles en el tablero
    for (int y = 0; y < BOARD_SIZE; y++) {
        for (int x = 0; x < BOARD_SIZE; x++) {
            Position to = { x, y };
            // Si encontramos al menos un movimiento válido, devolvemos true
            if (isValidMove(chessBoard, from, to, isWhiteTurn)) {
                return true; // 
            }
        }
    }
    return false; // No hay movimientos posibles
}

// Verifica si el movimiento es válido según las reglas del ajedrez

bool isValidMove(char chessBoard[BOARD_SIZE][BOARD_SIZE], Position from, Position to, bool isWhiteTurn) {
    char piece = chessBoard[from.y][from.x];  // La pieza que queremos mover
    char target = chessBoard[to.y][to.x];     // Lo que hay en la casilla destino

    // Calculamos la diferencia entre posiciones 
    int difx = to.x - from.x;  // Diferencia en columnas
    int dify = to.y - from.y;  // Diferencia en filas

	// Para el movimiento de la reina hemos utilizado IA y gracias a eso hemos ido haciendo nosotros el resto, tambíén tenemos duplicado dos veces el movimiento de la reina, cuando nos ayudó la IA lo puso y no sabemos por qué, pero lo hemos dejado así ya que cuando lo queremos quitar da errores.
    if (piece == WHITE_QUEEN || piece == BLACK_QUEEN) {

        // Primero: verificamos movimiento tipo torre (horizontal o vertical)
        if (difx == 0 || dify == 0) {

            // Si nos movemos verticalmente (misma columna)
            if (difx == 0) {
                int step = 1;
                if (dify < 0) {
                    step = -1; // Ajustamos dirección: arriba o abajo
                }
                // Comprobamos que no haya piezas en el camino
                for (int y = from.y + step; y != to.y; y += step) {
                    if (chessBoard[y][from.x] != EMPTY) {
                        return false; 
                    }
                }
                return true; // Movimiento vertical válido
            }
            // Si nos movemos horizontalmente (misma fila)
            if (dify == 0) {
                int step = 1;
                if (difx < 0) {
                    step = -1; // Ajustamos dirección: izquierda o derecha
                }
                // Comprobamos que no haya piezas en el camino
                for (int x = from.x + step; x != to.x; x += step) {
                    if (chessBoard[from.y][x] != EMPTY) {
                        return false; 
                    }
                }
                return true; // Movimiento horizontal válido
            }
        }

        // Segundo: verificamos movimiento del alfil
        if (difx == dify || difx == -dify) {
            int stepX = 1;
            int stepY = 1;
            if (difx < 0) {
                stepX = -1; // Ajustamos dirección: izquierda
            }
            if (dify < 0) {
                stepY = -1; // Ajustamos dirección: arriba
            }
            // Comprobamos que no haya piezas en la diagonal
            int x = from.x + stepX;
            int y = from.y + stepY;
            while (x != to.x && y != to.y) {
                if (chessBoard[y][x] != EMPTY) {
                    return false; 
                }
                x += stepX;
                y += stepY;
            }
            return true; // Movimiento diagonal válido
        }

        return false; // Si no es horizontal, vertical o diagonal, no es válido
    }


    // Verificamos que no estemos yendo donde hay  nuestras propias piezas
    if (isWhiteTurn) {
        // Si es turno de blancas y hay una pieza blanca en destino (letras mayúsculas)
        if (target >= 'A' && target <= 'Z') {
            return false; // No podemos ir donde hay nuestras propias piezas
        }
    }
    else {
        // Si es turno de negras y hay una pieza negra en destino (letras minúsculas)
        if (target >= 'a' && target <= 'z') {

			// AQUÍ ESTA LA DUPLICACIÓN DEL CÓDIGO DE LA REINA, NO SABEMOS POR QUÉ LO HIZO LA IA PERO SI LO QUITAMOS NO DETECTA BIEN ALGUNAS COSAS


            if (piece == WHITE_QUEEN || piece == BLACK_QUEEN) {
                // La reina se mueve como una torre O como un alfil
                // Comprobar movimiento de torre (horizontal o vertical)
                if (difx == 0 || dify == 0) {
                    // Código comprovación torre
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

                // Comprobar movimiento de alfil
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
            return false; // No podemos coger nuestras propias piezas
        }
    }

	// REGLAS PEÓN

    if (piece == WHITE_PAWN || piece == BLACK_PAWN) {
        int direction = 1;  // Dirección del movimiento: 1 para negras (hacia abajo)
        int startRow = 1;   // Fila inicial: 1 para negras

        if (piece == WHITE_PAWN) {
            direction = -1;  // Dirección para blancas: -1 (hacia arriba)
            startRow = BOARD_SIZE - 2;  // Fila inicial para blancas
        }

        // Movimiento normal de 1 casilla hacia adelante
        if (difx == 0 && dify == direction && target == EMPTY) {
            return true;
        }
        // Movimiento especial: 2 casillas desde posición inicial
        if (difx == 0 && dify == 2 * direction && from.y == startRow &&
            chessBoard[from.y + direction][from.x] == EMPTY && target == EMPTY) {
            return true;
        }
        // Captura en diagonal 
        if ((difx == 1 || difx == -1) && dify == direction && target != EMPTY) {
            return true;
        }

        return false; // Si no es ninguno de estos movimientos, no es válido
    }

    // REGLAS TORRE


    if (piece == WHITE_ROOK || piece == BLACK_ROOK) {
        // Movimiento vertical
        if (difx == 0) {
            int step = 1;
            if (dify < 0) {
                step = -1; // Ajustamos dirección
            }
            // Verificamos que el camino esté libre
            for (int y = from.y + step; y != to.y; y += step) {
                if (chessBoard[y][from.x] != EMPTY) {
                    return false; // Camino bloqueado
                }
            }
            return true; // Movimiento válido
        }
        // Movimiento horizontal
        if (dify == 0) {
            int step = 1;
            if (difx < 0) {
                step = -1; // Ajustamos dirección
            }
            // Verificamos que el camino esté libre
            for (int x = from.x + step; x != to.x; x += step) {
                if (chessBoard[from.y][x] != EMPTY) {
                    return false; // Camino bloqueado
                }
            }
            return true; // Movimiento válido
        }
        return false; // Si no es horizontal ni vertical, no es válido
    }

    // REGLAS CABALLO

    if (piece == WHITE_KNIGHT || piece == BLACK_KNIGHT) {
        // Solo verificamos que haga L : 2+1 o 1+2
        if ((difx == 2 && dify == 1) || (difx == 2 && dify == -1) ||
            (difx == -2 && dify == 1) || (difx == -2 && dify == -1) ||
            (difx == 1 && dify == 2) || (difx == 1 && dify == -2) ||
            (difx == -1 && dify == 2) || (difx == -1 && dify == -2)) {
            return true; 
        }
        return false;
    }

	// REGLAS ALFIL

    if (piece == WHITE_BISHOP || piece == BLACK_BISHOP) {
        // El alfil solo puede moverse en diagonal
        if (difx == dify || difx == -dify) {
            int stepX = 1;
            int stepY = 1;
            if (difx < 0) {
                stepX = -1; // Diagonal hacia izquierda
            }
            if (dify < 0) {
                stepY = -1; // Diagonal hacia arriba
            }
            // Verificamos que la diagonal esté libre
            int x = from.x + stepX;
            int y = from.y + stepY;
            while (x != to.x && y != to.y) {
                if (chessBoard[y][x] != EMPTY) {
                    return false; // Diagonal bloqueada
                }
                x += stepX;
                y += stepY;
            }
            return true; // Movimiento diagonal válido
        }
        return false; // Si no es diagonal, no es válido
    }

	// REGLAS REY

    if (piece == WHITE_KING || piece == BLACK_KING) {
        // El rey solo puede moverse 1 casilla en cualquier dirección
        if ((difx >= -1 && difx <= 1) && (dify >= -1 && dify <= 1)) {
            return true; // Movimiento válido
        }
        return false; // Movimiento inválido para el rey
    }

    return false; // Si llegamos aquí, el movimiento no es válido
}

// Verifica si un rey sigue vivo (existe en el tablero)
bool isKingAlive(char chessBoard[BOARD_SIZE][BOARD_SIZE], char king) {
    // Recorremos todo el tablero buscando al rey
    for (int y = 0; y < BOARD_SIZE; y++) {
        for (int x = 0; x < BOARD_SIZE; x++) {
            if (chessBoard[y][x] == king) {
                return true; // El rey sigue
            }
        }
    }
    return false; // RIP
}

// Permite al usuario seleccionar una pieza válida y moverla

void movePieceByUser(char chessBoard[BOARD_SIZE][BOARD_SIZE], bool isWhiteTurn) {
    Position from, to;  // Coordenadas de origen y destino
    bool isValidSelection = false;     // Si se selecciona una pieza válida
    bool isValidDestination = false;   // Si se selecciona un destino válido

    // Bucle para seleccionar una pieza válida
    do {
        std::cout << "------------------" << std::endl;
        // Indicamos de quién es el turno
        if (isWhiteTurn) {
            std::cout << "Turno de las BLANCAS" << std::endl;
        }
        else {
            std::cout << "Turno de las NEGRAS" << std::endl;
        }
        std::cout << "Elige una pieza (X Y): ";
        std::cin >> from.x >> from.y;
        std::cout << "------------------" << std::endl;

        // Verificamos que las coordenadas estén dentro del tablero

        if (from.x < 1 || from.x > BOARD_SIZE || from.y < 1 || from.y > BOARD_SIZE) {
            std::cout << "Posicion fuera del tablero. Intenta de nuevo." << std::endl;
            continue; // Volvemos a pedir input
        }

        // Que empiece del 1 - 8 pero en realidad es del 0 - 7
        from.x--;  
        from.y = BOARD_SIZE - from.y; 

        char selectedPiece = chessBoard[from.y][from.x];  // Pieza seleccionada

        // Verificamos que sea una selección válida

        if (selectedPiece == EMPTY) {
            std::cout << "No hay ninguna pieza en esa posicion." << std::endl;
        }
        else if (isWhiteTurn && (selectedPiece < 'A' || selectedPiece > 'Z')) {
            std::cout << "Esa pieza no te pertenece." << std::endl; // No es una pieza blanca
        }
        else if (!isWhiteTurn && (selectedPiece < 'a' || selectedPiece > 'z')) {
            std::cout << "Esa pieza no te pertenece." << std::endl; // No es una pieza negra
        }
        else if (!hasAnyValidMove(chessBoard, from, isWhiteTurn)) {
            std::cout << "Esa pieza no tiene movimientos validos. Elige otra." << std::endl;
        }
        else {
            isValidSelection = true; // Pieza valida
        }
    } while (!isValidSelection);

    // Bucle para seleccionar un destino válido

    do {
        std::cout << "Elige la posicion de destino (X Y): ";
        std::cin >> to.x >> to.y;

        // Verificamos que las coordenadas estén dentro del tablero
        if (to.x < 1 || to.x > BOARD_SIZE || to.y < 1 || to.y > BOARD_SIZE) {
            std::cout << "Posicion fuera del tablero. Intenta de nuevo." << std::endl;
            continue; // Volvemos a pedir input
        }

        // Convertimos a índices válidos del array
        to.x--;
        to.y = BOARD_SIZE - to.y;

        // Verificamos que el movimiento sea válido según las reglas del ajedrez
        if (isValidMove(chessBoard, from, to, isWhiteTurn)) {
            isValidDestination = true; // Valido
        }
        else {
            std::cout << "Movimiento no valido. Intenta de nuevo." << std::endl;
        }
    } while (!isValidDestination);

    // Ejecutamos el movimiento
    char piece = chessBoard[from.y][from.x];  // Guardamos la pieza
    chessBoard[from.y][from.x] = EMPTY;       // Vaciamos origen
    chessBoard[to.y][to.x] = piece;           // Colocamos pieza en destino



    // Verificamos si el rey enemigo ha sido eliminado 

    if (isWhiteTurn) {
        if (!isKingAlive(chessBoard, BLACK_KING)) {
            std::cout << "Las BLANCAS han ganado! El rey negro ha sido eliminado." << std::endl;
            exit(0); // Game over
        }
    }
    else {
        if (!isKingAlive(chessBoard, WHITE_KING)) {
            std::cout << "Las NEGRAS han ganado! El rey blanco ha sido eliminado." << std::endl;
            exit(0); // Game over
        }
    }
}