#ifndef PIECE_H_
#define PIECE_H_
#include <stdbool.h>
#include "space.h"

enum pieceType {pawn,rook,knight,bishop,queen,king};

struct Piece {
    bool isWhite; //this is really a bool
    enum pieceType piece_type;
};

//This functions could probably be improved to have one
//generic move that changes depending on the caller.
//This is polymorphism

bool move(struct Piece *piece, struct Space *from, struct Space *to);
struct Piece promote(struct Piece *pawn, enum pieceType newPiece); 
#endif
