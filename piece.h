#ifndef PIECE_H_
#define PIECE_H_
#include <stdbool.h>

#include "space.h"

bool move(struct Space *from, struct Space *to);

enum pieceType {pawn,rook,knight,bishop,queen,king};

struct Piece {
    bool isWhite; 
    enum pieceType piece_type;
};

//This functions could probably be improved to have one
//generic move that changes depending on the caller.
//This is polymorphism


//struct Piece promote(struct Piece *pawn, enum pieceType newPiece); 
#endif
