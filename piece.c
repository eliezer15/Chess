#include "piece.h"
#include "space.h"
#include <stdbool.h>
#include <stdlib.h>

bool movePawn(struct Space *from, struct Space *to);
bool moveRook(struct Space *from, struct Space *to);
bool moveKnight(struct Space *from, struct Space *to);
bool moveBishop(struct Space *from, struct Space *to);
bool moveQueen(struct Space *from, struct Space *to);
bool moveKing(struct Space *from, struct Space *to);
       
bool move(struct Space *from, struct Space *to) {
    if (from->piece == NULL) return false;

    switch(from->piece->piece_type) 
    {
        case pawn: return movePawn(from, to);
                   break; 
//      case rook: return moveRook(from, to);
//                   break; 
//        case knight: return moveKnight(from, to);
//                   break; 
//        case bishop: return moveBishop(from, to);
//                   break; 
//        case queen: return moveQueen(from, to);
//                   break; 
//        case king: return moveKing(from, to);
//                   break; 
    }
}

bool movePawn(struct Space *from, struct Space *to) {
    
    //1. If the pawn is not moving in a straing line, make sure it will move 
    //one space diagonally and will caputer another opposite piece

    if (from->col != to->col) {
        if (((from->col + 1 != to->col) && (from->col - 1 != to->col)) ||
            (from->row + 1 != to->row) || (to->piece == NULL) ||
            (from->piece->isWhite == to->piece->isWhite)){
                return false;
            }
    }
    
    //2. If it's moving straight, make sure it's just one space
    else if (from->row + 1 !=  to->row) return false;
    
    //3. If it's moving one row straight, make sure the space it's not occupied
    else if (to->piece) return false; 

    // The move is legal
    if (to->piece) free(to->piece); // if it is a capture, delete the piece that was captured
        
    to->piece = malloc(sizeof(struct Piece));
    to->piece = from->piece;
    
    free(from->piece);
    from->piece = NULL;

    return true;
    //WILL HANDLE PROMOTION AND INITIAL 2 SPACE OPEN LATER        
}

//struct Piece promote(struct Piece *pawn, enum pieceType newPiece) {}
