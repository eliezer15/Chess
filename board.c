#include "space.h"
#include "piece.h"
#include "board.h"
#include <stdio.h>
#define LOWERCASE 97
#define CASEOFFSET 32
/* Piece representation legend:
* R: Rook
* N:Knight
* B: Bishop
* Q: Queen
* K: King
* P: Pawn
*
* For simplicity purposes
* the black pieces will use uppercase letters
* 
*/

void printBoard(struct Space* board[][8]);

void printBoard(struct Space* board[][8]) {
    
    int i,j;
    char piece;
    
    //First print the letter columns
    printf("      "); //print 6 spaces for style
    for (i = 0; i < 8; i++) { 
        printf("%c     ", LOWERCASE + i);
    }

    for (i = 0; i < 8; i++) {
        
        printf("\n   -------------------------------------------------\n");
        printf("%d",i+1);

        for (j = 0; j < 8; j++) {
            //See if there is a piece on the space to print
            if (board[i][j]->piece) {
                switch(board[i][j]->piece->piece_type) 
                {
                    case(pawn):   piece = 'P';
                                  break;
                    case(rook):   piece = 'R';
                                  break;
                    case(knight): piece = 'N';
                                  break;
                    case(bishop): piece = 'B';
                                  break;
                    case(queen):  piece = 'Q';
                                  break;
                    case(king):   piece = 'K';
                                  break;
                    default:      piece = ' ';
                                  break;
                }

                if (board[i][j]->piece->isWhite)
                    piece += CASEOFFSET; //turn lowercase
            }
            
            else piece = ' ';
        
            printf("  |  ");
            printf("%c", piece);

        } 
        printf("  |  ");
   }
   printf("\n   ------------------------------------------------\n\n");
}
    
