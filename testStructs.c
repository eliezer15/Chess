#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "piece.h"
#include "space.h"

int main() {
    struct Piece* p;
    struct Space* s;
    p = malloc(sizeof(struct Piece));
    p->isWhite = true;
    p->piece_type = pawn;
    
    s = malloc(sizeof(struct Space));
    s->piece = p;
    s->col = 0;
    s->row = 0;
    
    printf("%d, %d\n", p->isWhite, p->piece_type);
    printf("%p, %d\n", s->piece, s->row);
    return 0;
}

