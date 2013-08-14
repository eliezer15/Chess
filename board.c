#include "space.h"
#include "piece.h"
#include "board.h"
#include <stdio.h>
#define LOWERCASE 97

void printBoard(struct Space* board[][8]);

void printBoard(struct Space* board[][8]) {
    
    int i,j;
    
    //First print the letter columns
    for (i = 0; i < 8; i++) 
        printf("%c  ", LOWERCASE + i);
    
}
    
