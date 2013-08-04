#include "piece.h"
#include "space.h"
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

bool movePawn(struct Space *from, struct Space *to);
bool moveRook(struct Space *from, struct Space *to);
bool moveKnight(struct Space *from, struct Space *to);
bool moveBishop(struct Space *from, struct Space *to);
bool moveQueen(struct Space *from, struct Space *to);
bool moveKing(struct Space *from, struct Space *to);
       
bool move(struct Space *from, struct Space *to) {
    if (from->piece == NULL) return false;
    if (to->piece != NULL && from->piece->isWhite == to->piece->isWhite) 
        return false;

    bool valid;

    switch(from->piece->piece_type) 
    {
        case pawn: valid = movePawn(from, to);
                   break; 
        case rook: valid = moveRook(from, to);
                   break; 
        case knight: valid = moveKnight(from, to);
                   break; 
        case bishop: valid = moveBishop(from, to);
                   break; 
        case queen: valid = moveQueen(from, to);
                   break; 
        case king: valid = moveKing(from, to);
                   break; 
        default: return true;
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

bool movePawn(struct Space *from, struct Space *to) {
    
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

bool moveRook(struct Space *from, struct Space *to) {
    //1. Movement can only be horizontal or vertical, no exception
    return ((from->col == to->col) || (from->row == to->row));
}

bool moveKnight(struct Space *from, struct Space *to) {
    return true; 
    //IMPLEMENT LATER
}

bool moveBishop(struct Space *from, struct Space *to) {
    //1.Movement only vertical
    int colOffset = abs(from->col - to->col); //abs is absolute value
    int rowOffset = abs(from->row - to->row);
    
    return (colOffset == rowOffset);
}

bool moveQueen(struct Space *from, struct Space *to) {
    //1.Movement like the rook or bishop
    return (moveRook(from,to) || moveBishop(from,to));
}

bool moveKing(struct Space *from, struct Space *to) {
    int colOffset = abs(from->col - to->col);
    int rowOffset = abs(from->row - to->row);
    
    //1.Movement like queen, but only one space
    return ((colOffset == 1 && rowOffset == 1) && moveQueen(from,to));

    //LATER DON'T ALLOW KING TO MOVE INTO CHECK;
}

//struct Piece promote(struct Piece *pawn, enum pieceType newPiece) {}
