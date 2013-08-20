#include "board.h"
#include "piece.h"
#include "space.h"
#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>

/* Notes
* I allocate space in the array for 10 major pieces(except on King) because it is possible
* to have as many as 10, considering all 8 pawns promote to the given
* piece. Very unlikely, but technically possible.
*/

void initializeBoard(struct Space* board[][8]);
void initializePieces(struct Piece* piece[], int N, enum pieceType type, bool areWhite);
bool parseCommand(char* from, char* to, int* fromRow, int* fromCol, int* toRow, int* toCol);

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
    
    //Kings are put in array to use 
    //the initializePieces function
    //and reduce code
    struct Piece* whiteKing[1];
    struct Piece* blackKing[1];
       
    int i,j;
    
    initializeBoard(board);

    initializePieces(whitePawns, 8, pawn, true);
    initializePieces(blackPawns, 8, pawn, false);

    initializePieces(whiteRooks, 2, rook, true);
    initializePieces(blackRooks, 2, rook, false);

    initializePieces(whiteBishops, 2, bishop, true);
    initializePieces(blackBishops, 2, bishop, false);

    initializePieces(whiteKnights, 2, knight, true);
    initializePieces(blackKnights, 2, knight, false);

    initializePieces(whiteQueens, 1, queen, true);
    initializePieces(blackQueens, 1, queen, false);

    initializePieces(whiteKing, 1, king, true);
    initializePieces(blackKing, 1, king, false);
    
    //Place pieces on boards
    //pawns
    for (i = 0; i < 8; i++) {
        board[1][i]->piece = whitePawns[i];
        board[6][i]->piece = blackPawns[i];
    }
    
    //rooks
    board[0][0]->piece = whiteRooks[0];
    board[0][7]->piece = whiteRooks[1];
    board[7][0]->piece = blackRooks[0];
    board[7][7]->piece = blackRooks[1];

    //knights
    board[0][1]->piece = whiteKnights[0];
    board[0][6]->piece = whiteKnights[1];
    board[7][1]->piece = blackKnights[0];
    board[7][6]->piece = blackKnights[1];

    //bishops
    board[0][2]->piece = whiteBishops[0];
    board[0][5]->piece = whiteBishops[1];
    board[7][2]->piece = blackBishops[0];
    board[7][5]->piece = blackBishops[1];

    //queens
    board[0][4]->piece = whiteQueens[0];
    board[7][3]->piece = blackQueens[0];

    //kings
    board[0][3]->piece = whiteKing[0];
    board[7][4]->piece = blackKing[0];

    //start game
    int *fromCol, *fromRow, *toCol, *toRow;
    //initialize pointers
    fromCol = malloc(sizeof(int));
    fromRow = malloc(sizeof(int));
    toCol = malloc(sizeof(int));
    toRow = malloc(sizeof(int));
     
    char *from = malloc(sizeof(from));
    char *to = malloc(sizeof(to));

    while (true) {
        printBoard(board);    
       
        scanf("%s %s", from, to); 

        if (parseCommand(from, to, fromRow, fromCol, toRow, toCol)) 
            move(board[*fromRow][*fromCol], board[*toRow][*toCol], board);
        else 
            printf("Invalid command\n");
        
    }

    return 0;
}

void initializeBoard(struct Space* board[][8]) {
    int i,j;
    for (i = 0; i < 8; i++)
        for (j = 0; j < 8; j++) {
            board[i][j] = malloc(sizeof(struct Space));
            board[i][j]->row = i;
            board[i][j]->col = j;
        }
}

void initializePieces(struct Piece* piece[], int N, enum pieceType type, bool areWhite) {
    
    int i;
    for (i = 0; i < N; i++) {
        piece[i] = malloc(sizeof(struct Piece));
        piece[i]->piece_type = type;
        piece[i]->isWhite = areWhite;
    }
}

bool parseCommand(char* from, char* to, int* fromRow, int* fromCol, int* toRow, int* toCol) {
    
    int i;
    for (i = 0; i < 2; i++)
        printf("%c %c\n", from[i], to[i]);

    if (from[0] < 'a' ||  from[0] > 'h')
        return false;
    if (from[1] < 49 || from[1] > 56) //49 to 56 are the char representations of 1 through 8
        return false;
    if (to[0] < 'a' || to[0] > 'h')
        return false;
    if (to[1] < 49 || to[1] > 56)
        return false;

    *fromCol = from[0] -'a';
    *fromRow = from[1] -'1';
    *toCol = to[0] - 'a';
    *toRow = to[1] - '1';
    return true;
}

