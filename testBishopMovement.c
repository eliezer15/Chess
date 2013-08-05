#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "piece.h"
#include "space.h"

/* This file includes tests for motion for the bishop */
int main() {
    struct Space* board[8][8];
    struct Piece* bishops[3];

    int i,j,k;
    
    for (k = 0; k < 3; k++) {
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

    board[0][0]->piece = bishops[1]; //white bishop to space a1
    board[7][0]->piece = bishops[2]; //white bishop to space a8
    board[7][7]->piece = bishops[0]; //black bishop to space h8
    
    //Tests
    int N = 8;
    bool test[N];

    //All tests should evaluate to true; 
    test[0] = !(move(board[0][0], board[0][7])); //Move a1 horizontally to h1
    test[1] = !(move(board[0][0], board[7][1])); //Move a1 randomly to b8
    test[2] = (move(board[7][0], board[0][7])); //Move a8, to h1
    test[3] = (move(board[0][7], board[4][3])); //Move h1 to d5
    test[4] = !(move(board[0][0], board[4][3])); //Move a1 to d5 where same color piece is
    test[5] = (move(board[4][3], board[7][0])); //Move d5 to a8 
    test[6] = (move(board[0][0], board[7][7])); //Move a1 to h8 and capture black piece
    test[7] = ((board[7][7]->piece->isWhite)); //Make sure a white piece is on h8

    int a;
    char* message = NULL;
    for (a = 0; a < N; a++) {
        if (test[a])
            message = "Success!";
        else
            message = "Failure!";
        printf("Test %d was a %s\n",a,message);
    }
    return 0;
}

