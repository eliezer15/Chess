#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "piece.h"
#include "space.h"

int main() {

    struct Piece *p = malloc(sizeof(struct Piece));
    struct Space *s = malloc(sizeof(struct Space));

    s->piece = p;
    free(s->piece);
    s->piece = NULL;
    return 0;
}
