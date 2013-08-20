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
bool parseCommand(char* command, int* fromRow, int* fromCol, int* toRow, int* toCol);

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
    board[7][2]->piece = blackRooks[0];
    board[7][5]->piece = blackRooks[1];

    //queens
    board[0][4]->piece = whiteQueens[0];
    board[7][3]->piece = blackQueens[0];

    //kings
    board[0][3]->piece = whiteKing[0];
    board[7][4]->piece = blackKing[0];

    //start game
    int *fromCol, *fromRow, *toCol, *toRow;
    char *command;

    while (true) {
        printBoard(board);    
       
        scanf("%s", &command); 
        printf("%s\n", command);

        if (parseCommand(command, fromRow, fromCol, toRow, toCol)) 
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

bool parseCommand(char command[], int* fromRow, int* fromCol, int* toRow, int* toCol) {
    
    //int i;
    //for (i = 0; i < 6; i++)
    //    printf("%c\n", command[i]);

    if (command[0] >=  'a' &&  command[0] <= 'h')
        return false;
    if (command[1] >= 49 && command[1] <= 56) //49 to 56 are the char representations of 1 through 8
        return false;
    if (command[2] != 32) //32 is Space
        return false;
    if (command[3] >= 'a' && command[3] <= 'h')
        return false;
    if (command[4] >= 49 && command[4] <= 56)
        return false;

    *fromCol = command[0] -'a';
    *fromRow = command[1] -'1';
    *toCol = command[3] - 'a';
    *toRow = command[4] - '1';
    return true;
}

