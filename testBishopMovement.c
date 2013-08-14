#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "piece.h"
#include "space.h"

/* This file includes tests for motion for the bishop */
int main() {

    int pieces = 4;
    int tests = 10;

    struct Space* board[8][8];
    struct Piece* bishops[pieces];

    int i,j,k;
    
    for (k = 0; k < pieces; k++) {
        bishops[k] = malloc(sizeof(struct Piece));
        bishops[k]->isWhite = k; //one will be False
        bishops[k]->piece_type = bishop;
     }
     
    for (i = 0; i < 8; i++) {
        for (j = 0; j < 8; j++) {
            board[i][j] = malloc(sizeof(struct Space));
            board[i][j]->row = i;
            board[i][j]->col = j;
         }
    }

    board[7][7]->piece = bishops[0]; //black bishop to space h8
    board[0][0]->piece = bishops[1]; //white bishop to space a1
    board[7][0]->piece = bishops[2]; //white bishop to space a8
    board[3][3]->piece = bishops[3]; //white bishop to space d4 
    //Tests
    bool test[tests];

    //All tests should evaluate to true; 
    test[0] = !(move(board[0][0], board[0][7], board)); //Move a1 horizontally to h1
    test[1] = !(move(board[0][0], board[7][1], board)); //Move a1 randomly to b8
    test[2] = !(move(board[0][0], board[6][6], board)); //Move a1 to g7, with a piece on the path (d4) 
    test[3] = !(move(board[7][7], board[1][1], board)); //Move h8 to b2, with a piece on the path (d4)
    test[4] = (move(board[7][0], board[0][7], board)); //Move a8, to h1
    test[5] = (move(board[0][7], board[4][3], board)); //Move h1 to d5
    test[6] = !(move(board[0][0], board[4][3], board)); //Move a1 to d5 where same color piece is
    test[7] = (move(board[4][3], board[7][0], board)); //Move d5 to a8 
    test[8] = (move(board[3][3], board[7][7], board)); //Move d4 to h8 and capture black piece
    test[9] = ((board[7][7]->piece->isWhite, board)); //Make sure a white piece is on h8
    
    int a;
    char* message = NULL;
    for (a = 0; a < tests; a++) {
        if (test[a])
            message = "Success!";
        else
            message = "Failure!";
        printf("Test %d was a %s\n",a,message);
    }
    return 0;
}

