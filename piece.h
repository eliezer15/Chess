#ifndef PIECE_H_
#define PIECE_H_
#include <stdbool.h>

#include "space.h"

bool move(struct Space *from, struct Space *to, struct Space *board[][8], bool isWhiteTurn);

enum pieceType {pawn,rook,knight,bishop,queen,king};

struct Piece {
    bool isWhite; 
    enum pieceType piece_type;
    struct Space *space; //only needed for King
};

//This functions could probably be improved to have one
//generic move that changes depending on the caller.
//This is polymorphism


//struct Piece promote(struct Piece *pawn, enum pieceType newPiece); 
#endif
