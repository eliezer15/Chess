#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "piece.h"
#include "space.h"

/* This file includes tests for motion for the pawn */
int main() {
    struct Space* board[8][8];
    struct Piece* pawns[3];

    int i,j,k;
    
    for (k = 0; k < 3; k++) {
        pawns[k] = malloc(sizeof(struct Piece));
        pawns[k]->isWhite = k; //one will be False
        pawns[k]->piece_type = pawn;
     }
     
    for (i = 0; i < 8; i++) {
        for (j = 0; j < 8; j++) {
            board[i][j] = malloc(sizeof(struct Space));
            board[i][j]->row = i;
            board[i][j]->col = j;
         }
    }

    board[1][2]->piece = pawns[1]; //black pawn to space c2
    board[2][1]->piece = pawns[2]; //black pawn to space b3
    board[2][3]->piece = pawns[0]; //white pawn to space d3

    //Tests
    bool test[11];

    //All tests should evaluate to true 
    test[0] = !(move(board[0][0], board[0][1])); //Move a spot where there is no piece:
    test[1] = !(move(board[1][2], board[4][2])); //Move c2 to e3: 
    test[2] = !(move(board[1][2], board[0][1])); //Move c2 to a3: 
    test[3] = !(move(board[1][2], board[0][2])); //Move c2 to c1: 
    test[4] = !(move(board[1][2], board[3][2])); //Move c2 to c4: THIS ONE SHOULD BE PERMITTED LATER ON
    test[5] = !(move(board[1][2], board[2][1])); //Move c2 to b3 and eat another black piece: 
    test[6] = !(move(board[1][2], board[1][3])); //Move c2 to d2: 
    test[7] = move(board[1][2], board[2][3]); //Move c2 to d3 and eat white piece:
    test[8] = !((board[2][3]->piece->isWhite)); //A black piece is now in d3: 
    test[9] = (board[1][2]->piece == NULL); //There is no piece in c2: 
    test[10] = move(board[2][3],board[3][3]); //Move d3 to d4: 

    int a;
    char* message = NULL;
    for (a = 0; a < 11; a++) {
        if (test[a])
            message = "Success!";
        else
            message = "Failure!";
        printf("Test %d was a %s\n",a,message);
    }
    return 0;
}

