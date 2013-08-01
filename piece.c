#include "piece.h"
#include "space.h"
#include <stdbool.h>

bool movePawn(struct Piece *piece, struct Space *from, struct Space *to);
//bool moveRook(struct Piece *piece, struct Space *from, struct Space *to);
//bool moveKnight(struct Piece *piece, struct Space *from, struct Space *to);
//bool moveBishop(struct Piece *piece, struct Space *from, struct Space *to);
//bool moveQueen(struct Piece *piece, struct Space *from, struct Space *to);
//bool moveKing(struct Piece *piece, struct Space *from, struct Space *to);
       
bool move(struct Piece *piece, struct Space *from, struct Space *to) {
    switch(piece->piece_type) 
    {
        case pawn: return movePawn(piece, from, to);
                   break; 
        //case rook: return moveRook(&piece, &from, &to);
        //           break; 
        //case knight: return moveKnight(&piece, &from, &to);
        //           break; 
        //case bishop: return moveBishop(&piece, &from, &to);
        //           break; 
        //case queen: return moveQueen(&piece, &from, &to);
        //           break; 
        //case king: return moveKing(&piece, &from, &to);
         //          break; 
    }
}
bool movePawn(struct Piece *piece, struct Space *from, struct Space *to) {
    return true;
}


//struct Piece promote(struct Piece *pawn, enum pieceType newPiece) {}
