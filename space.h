#ifndef SPACE_H_
#define SPACE_H_
#include "piece.h"

struct Space {
    struct Piece *piece;
    int row;
    int col;
};

#endif
