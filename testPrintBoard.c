#include "board.h"
#include "piece.h"
#include "space.h"

int main() {
    
    struct Space* board[8][8];
    printBoard(board);
    
    return 0;

}
