#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "piece.h"
#include "space.h"

/* This file includes tests for motion for the rook */
int main() {
    struct Space* board[8][8];
    struct Piece* rooks[3];

    int i,j,k;
    
    for (k = 0; k <5 ; k++) {
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

    board[0][0]->piece = rooks[1]; //white rook to space a1
    board[7][0]->piece = rooks[2]; //white rook to space a8
    board[0][7]->piece = rooks[0]; //black rook to space h1
    board[4][0]->piece = rooks[3];
    board[0][4]->piece = rooks[4];


    //Tests
    bool test[11];
    move(board[0][1], board[0][0], board);
    //All tests should evaluate to true; 
   // test[2] = !(move(board[0][0], board[7][0]), board); //Move a1 to a8, where a same color piece is
   // test[3] = (move(board[7][0], board[7][7]), board); //Move a8 horizontally to h8
   // //test[4] = (board[7][7]->piece);
   // test[4] = (move(board[7][7], board[7][0]), board); //Move h8 back a8
   // test[5] = (move(board[0][0], board[6][0]), board); //Move a1 vertically to a7 
   // test[6] = (move(board[6][0], board[0][0]), board); //Move a7 back to a1
   // test[7] = (move(board[0][0], board[0][7]), board); //Move a1 to h1 and capture black
   // test[8] = ((board[0][7]->piece->isWhite)); //Make sure a white piece is on h1
   // test[9] = !(move(board[0][0], board[0][6]), board);
   // test[10] = !(move(board[0][0], board[6][0]), board);

    int a;
    char* message = NULL;
    for (a = 0; a < 9; a++) {
        if (test[a])
            message = "Success!";
        else
            message = "Failure!";
        printf("Test %d was a %s\n",a,message);
    }
    return 0;
}

