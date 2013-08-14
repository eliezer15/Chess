#include "board.h"
#include "piece.h"
#include "space.h"
#include <stdbool.h>
#include <stdlib.h>
/* Notes
* I allocate space in the array for 10 major pieces(except on King) because it is possible
* to have as many as 10, considering all 8 pawns promote to the given
* piece. Very unlikely, but technically possible.
*/
int main() {
    
    struct Space* board[8][8];
    
    struct Piece* whitePawns[8];
    struct Piece* blackPawns[8];

    struct Piece* whiteRooks[10];
    struct Piece* blackRooks[10];

    struct Piece* whiteBishops[10];
    struct Piece* blackBishops[10];
    
    struct Piece* whiteKnights[10];
    struct Piece* blackKnights[10];
    
    struct Piece* whiteQueens[10];
    struct Piece* blackQueens[10];
    
    struct Piece* whiteKing;
    struct Piece* blackKing;
    
   
    int i,j;

    //Initialize board
    for (i = 0; i < 8; i++)
        for (j = 0; j < 8; j++)
            board[i][j] = malloc(sizeof(struct Space));

    //Initialize pawns
    for (i = 0; i < 8; i++) {
        whitePawns[i] = malloc(sizeof(struct Piece));
        whitePawns[i]->piece_type = pawn;
        whitePawns[i]->isWhite = true;
        board[1][i]->piece = whitePawns[i];
    
        blackPawns[i] = malloc(sizeof(struct Piece));
        blackPawns[i]->piece_type = pawn;
        blackPawns[i]->isWhite = false;
        board[6][i]->piece = blackPawns[i];
    } 

    printBoard(board);
    
    return 0;

}
