#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "piece.h"
#include "space.h"

/* This file includes tests for motion for the knight */
int main() {
    struct Space* board[8][8];
    struct Piece* knights[4];

    int i,j,k;
    
    for (k = 0; k < 4; k++) {
        knights[k] = malloc(sizeof(struct Piece));
        knights[k]->isWhite = k; //one will be False
        knights[k]->piece_type = knight;
     }
     
    for (i = 0; i < 8; i++) {
        for (j = 0; j < 8; j++) {
            board[i][j] = malloc(sizeof(struct Space));
            board[i][j]->row = i;
            board[i][j]->col = j;
         }
    }

    board[3][3]->piece = knights[1]; //white knight to space d4
    board[0][0]->piece = knights[2]; //white knight to space a1
    board[7][7]->piece = knights[3]; //white knight to space h8
    board[5][4]->piece = knights[0]; //black knight to space e6
    
    //Tests
    int N = 7;
    bool test[N];

    //All tests should evaluate to true; 
    test[0] = !(move(board[0][0], board[0][7])); //Move a1 horizontally to h1
    test[1] = !(move(board[0][0], board[7][1])); //Move a1 randomly to b8
    test[2] = (move(board[7][7], board[6][5])); //Move h8 to f7
    test[3] = !(move(board[5][1], board[7][0])); //Move b6 back to a8
    test[4] = (move(board[6][5], board[7][7])); //Move f7 back to h8
    test[5] = (move(board[3][3], board[5][4])); //Move d4 to e6 and capture black piece
    test[6] = ((board[5][4]->piece->isWhite)); //Make sure a white piece is on h8

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

