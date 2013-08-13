#include "piece.h"
#include "space.h"
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#define MAX(X,Y) (((X) > (Y)) ? (X) : (Y))
#define MIN(X, Y) (((X) < (Y)) ? (X) : (Y))

bool movePawn(struct Space *from, struct Space *to, struct Space *board[][8], int colOffset, int rowOffset);
bool moveRook(struct Space *from, struct Space *to, struct Space *board[][8]);
bool moveKnight(struct Space *from, struct Space *to, struct Space *board[][8], int colOffset, int rowOffset);
bool moveBishop(struct Space *from, struct Space *to, struct Space *board[][8], int colOffset, int rowOffset);
bool moveQueen(struct Space *from, struct Space *to, struct Space *board[][8], int colOffset, int rowOffset);
bool moveKing(struct Space *from, struct Space *to, struct Space *board[][8], int colOffset, int rowOffset);
       
bool move(struct Space *from, struct Space *to, struct Space *board[][8]) {
    if (from->piece == NULL) return false;
    //Check there is not a same colored piece on the spot
    if (to->piece != NULL && from->piece->isWhite == to->piece->isWhite) 
        return false;
    
    //Calculate offsets
    int colOffset = abs(from->col - to->col); //abs is absolute value
    int rowOffset = abs(from->row - to->row);
   
    bool valid;

    switch(from->piece->piece_type) 
    {
        case pawn: valid = movePawn(from, to, board, colOffset, rowOffset);
                   break; 
        case rook: valid = moveRook(from, to, board);
                   break; 
        case knight: valid = moveKnight(from, to, board, colOffset, rowOffset);
                   break; 
        case bishop: valid = moveBishop(from, to, board, colOffset, rowOffset);
                   break; 
        case queen: valid = moveQueen(from, to, board, colOffset, rowOffset);
                   break; 
        case king: valid = moveKing(from, to, board ,colOffset, rowOffset);
                   break; 
        default: return false;
    }
    
    
    if (valid) {
        if (to->piece) free(to->piece);
        
        to->piece = malloc(sizeof(struct Piece));
        memcpy(to->piece, from->piece, sizeof(struct Piece));
        free(from->piece);
        from->piece = NULL;        
    }

    return valid;
}

bool movePawn(struct Space *from, struct Space *to, struct Space *board[][8], int colOffset, int rowOffset) {
    
    //1. If the pawn is not moving in a straing line, make sure it will move 
    //one space diagonally and will caputer another opposite piece

    if (from->col != to->col) {
        if (((from->col + 1 != to->col) && (from->col - 1 != to->col)) ||
            (from->row + 1 != to->row) || (to->piece == NULL)){
                return false;
            }
    }
    
    //2. If it's moving straight, make sure it's just one space
    else if (from->row + 1 !=  to->row) return false;
    
    //3. If it's moving one row straight, make sure the space it's not occupied
    else if (to->piece) return false; 

    // The move is legal
    return true;
    //WILL HANDLE PROMOTION AND INITIAL 2 SPACE OPEN LATER        
}

bool moveRook(struct Space *from, struct Space *to, struct Space *board[][8]) {
    //1. Movement can only be horizontal or vertical, no exception
    if ((from->col != to->col) && (from->row != to->row)) return false;
    
    int i,start,end;

    //if motion is vertical
    if ((from->col == to->col)) {

        start = MIN(from->row, to->row); //start from the 'lower value'
        end = MAX(from->row, to->row);

        for (i = start+1; i < end; i++) {
            if (board[i][from->col]->piece)
                return false;
         }
    }
    
    //if motion is horizontal
    else if ((from->row == to->row)) {
   
        start = MIN(from->col, to->col); //start from the 'lower value'
        end = MAX(from->col, to->col);

        for (i = start+1; i < end; i++) {
            if (board[from->row][i]->piece)
                return false;
         }
    }

    return true;
}

bool moveKnight(struct Space *from, struct Space *to, struct Space *board[][8], int colOffset, int rowOffset) {
    //1. Movement is L shaped;
    return ((colOffset == 2 && rowOffset == 1) || (colOffset == 1 && rowOffset == 2));
}

bool moveBishop(struct Space *from, struct Space *to, struct Space *board[][8], int colOffset, int rowOffset) {
    //1.Movement only vertical
    
    return (colOffset == rowOffset);
}

bool moveQueen(struct Space *from, struct Space *to, struct Space *board[][8], int colOffset, int rowOffset) {
    //1.Movement like the rook or bishop
    return (moveRook(from,to, board) || moveBishop(from,to, board, colOffset, rowOffset));
}

bool moveKing(struct Space *from, struct Space *to, struct Space *board[][8], int colOffset, int rowOffset) {
    //1.Movement like queen, but only one space
    return ((colOffset <= 1 && rowOffset <= 1) && moveQueen(from,to, board, colOffset, rowOffset));

    //LATER DON'T ALLOW KING TO MOVE INTO CHECK;
}

//struct Piece promote(struct Piece *pawn, enum pieceType newPiece) {}
