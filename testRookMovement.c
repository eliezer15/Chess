#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "piece.h"
#include "space.h"

/* This file includes tests for motion for the rook */
int main() {
    
    int pieces = 5;
    int tests = 9;

    struct Space* board [8][8];
    struct Piece* rooks[pieces];

    int i,j,k;
    
    for (k = 0; k <pieces ; k++) {
        rooks[k] = malloc(sizeof(struct Piece));
        rooks[k]->isWhite = k; //one will be False
        rooks[k]->piece_type = rook;
     }
   
   for (i = 0; i < 8; i++) {
        for (j = 0; j < 8; j++) {
            board[i][j] = malloc(sizeof(struct Space));
            board[i][j]->row = i;
            board[i][j]->col = j;
         }
    }
    
    board[0][7]->piece = rooks[0]; //black rook to space h1
    board[0][0]->piece = rooks[1]; //white rook to space a1
    board[7][0]->piece = rooks[2]; //white rook to space a8
    board[4][0]->piece = rooks[3]; //white rook to space a3
    board[0][4]->piece = rooks[4]; //white rook to space e1
   

    //Tests
    bool test[tests];
    //All tests should evaluate to true; 
    test[0] = !(move(board[0][0], board[3][3], board)); //Move a1 diagonally to d4
    test[1] = !(move(board[0][0], board[7][1], board)); //Move a1 randomly to b8
    test[2] = !(move(board[0][0], board[7][0], board)); //Move a1 to a8, where a same color piece is
    test[3] = (move(board[7][0], board[7][7], board)); //Move a8 horizontally to h8
    test[4] = (move(board[7][7], board[7][0], board)); //Move h8 back a8
    test[5] = !(move(board[0][0], board[6][0], board)); //Move a1 vertically to a7 
    test[6] = !(move(board[0][0], board[0][5], board)); //Move a1 horizontally to f1
    test[7] = (move(board[0][4], board[0][7], board)); //Move e1 to h1 and capture black
    test[8] = ((board[0][7]->piece->isWhite)); //Make sure a white piece is on h1
    

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

