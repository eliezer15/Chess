#include "board.h"
#include "piece.h"
#include "space.h"
#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>

/* Notes
* I allocate space in the array for 10 major pieces(except on King) because it is possible
* to have as many as 10, considering all 8 pawns promote to the given
* piece. Very unlikely, but technically possible.
*/

void initializeBoard(struct Space* board[][8]);
void initializePieces(struct Piece* pieces[],  bool areWhite);
bool parseCommand(char* fromValues, char* toValues, struct Space* board[][8], struct Space** from, struct Space** to);
bool isKingChecked(struct Space* board[][8], struct Space* kingPosition);

int main() {
    
    struct Space* board[8][8];
    
    /* 0-7: pawns
     * 8-9: rooks
     * 10-11: knights
     * 12-13: bishops
     * 14: queen
     * 15: king
    */

    struct Piece* blackPieces[16];
    struct Piece* whitePieces[16];
       
    int i,j;
    
    initializeBoard(board);
    initializePieces(blackPieces, false);
    initializePieces(whitePieces, true);

    //Place pieces on boards
    //pawns
    for (i = 0; i < 8; i++) {
        board[1][i]->piece = whitePieces[i];
        board[6][i]->piece = blackPieces[i];
    }
    
    //rooks
    board[0][0]->piece = whitePieces[8];
    board[0][7]->piece = whitePieces[9];
    board[7][0]->piece = blackPieces[8];
    board[7][7]->piece = blackPieces[9];

    //knights
    board[0][1]->piece = whitePieces[10];
    board[0][6]->piece = whitePieces[11];
    board[7][1]->piece = blackPieces[10];
    board[7][6]->piece = blackPieces[11];

    //bishops
    board[0][2]->piece = whitePieces[12];
    board[0][5]->piece = whitePieces[13];
    board[7][2]->piece = blackPieces[12];
    board[7][5]->piece = blackPieces[13];

    //queens
    board[0][4]->piece = whitePieces[14];
    board[7][3]->piece = blackPieces[14];

    //kings. Note: only kings need to know their position
    board[0][3]->piece = whitePieces[15];
    whitePieces[15]->space = board[0][3];
    board[7][4]->piece = blackPieces[15];
    blackPieces[15]->space = board[7][4];

    //start game
    bool isWhiteTurn = true;
    struct Piece *king;
    king = whitePieces[15];
    bool validMove = true;
    bool checked = false;
    char *prompt = "White: ";

    //initialize space pointers
    struct Space *from;
    struct Space *to;
    
    char *fromValues = malloc(sizeof(fromValues));
    char *toValues = malloc(sizeof(toValues));
    
    printBoard(board);    
    //Game Loop
    while (true) {
        
        if (isKingChecked(board, king->space)) {
            printf("Checked!\n");
            checked = true;
        }

        printf("%s", prompt);
        scanf("%s %s", fromValues, toValues); 
        
        if (parseCommand(fromValues, toValues, board, &from, &to)) { //if command is valid
            
            if (checked && from->piece != king) {
                printf("Your King is checked. You must move it\n");
                continue;
            }
            
            if (from->piece == NULL) {
                printf("No piece found in that space\n");
                continue;
            }
  
            if (from->piece->isWhite != isWhiteTurn) {
                printf("You cannot move a piece of that color\n");
                continue;
            }
           
            if (to->piece != NULL && from->piece->isWhite == to->piece->isWhite) {
                printf("Cannot move a piece to a space occupied by a piece of the same color\n");
                continue;
            }

            if (from == to) {
                printf("Cannot move a piece to the same space it occupies\n");
                continue;
            }
            
            if (!move(from, to, board, isWhiteTurn)){
                printf("That move is not allowed\n");
                continue;
           }
           
           //No errors, so change turns
           isWhiteTurn = !isWhiteTurn;
           prompt = (isWhiteTurn) ? "White: ": "Black: ";
           
        }
        else 
            printf("Invalid command\n");
        
        
        printBoard(board);
    }

    return 0;
}

void initializeBoard(struct Space* board[][8]) {
    int i,j;
    for (i = 0; i < 8; i++)
        for (j = 0; j < 8; j++) {
            board[i][j] = malloc(sizeof(struct Space));
            board[i][j]->row = i;
            board[i][j]->col = j;
        }
}

void initializePieces(struct Piece* pieces[], bool areWhite) {
    
    int i;
    for (i = 0; i < 16; i++) {
        pieces[i] = malloc(sizeof(struct Piece));
        pieces[i]->isWhite = areWhite;
    }
    //All pieces are pawns by default (thank God)
    pieces[8]->piece_type = rook;
    pieces[9]->piece_type = rook;
    pieces[10]->piece_type = knight;
    pieces[11]->piece_type = knight;
    pieces[12]->piece_type = bishop;
    pieces[13]->piece_type = bishop;
    pieces[14]->piece_type = queen;
    pieces[15]->piece_type = king;
}

bool parseCommand(char* fromValues, char* toValues, struct Space* board[][8], struct Space** from, struct Space** to) {
    
    int fromCol, fromRow, toCol, toRow;
    if (fromValues[0] < 'a' ||  fromValues[0] > 'h')
        return false;
    if (fromValues[1] < 49 || fromValues[1] > 56) //49 to 56 are the char representations of 1 through 8
        return false;
    if (toValues[0] < 'a' || toValues[0] > 'h')
        return false;
    if (toValues[1] < 49 || toValues[1] > 56)
        return false;

    fromCol = fromValues[0] -'a';
    fromRow = fromValues[1] -'1';
    toCol = toValues[0] - 'a';
    toRow = toValues[1] - '1';
    
    *from = board[fromRow][fromCol]; 
    *to = board[toRow][toCol];

    return true;
}

bool isKingChecked(struct Space* board[][8], struct Space* kingPosition) {

    //Go over all pieces and see if any of them can legally move to where the King is, thus putting it on check
    int i,j;
    for(i = 0; i < 8; i++) {
        for(j = 0; j < 8; j++) {
            if (board[i][j]->piece) {
                if (move(board[i][j], kingPosition, board, board[i][j]->piece->isWhite))
                    return true;
            }
        }
    }

    return false;
}

