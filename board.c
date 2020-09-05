#include "board.h"

//#include <stdio.h>

#define kDefBoardWidth 5
#define kDefBoardHeight 5

#define kMaxScore 4

#define kFlagNote0 0x01
#define kFlagNote1 0x02
#define kFlagNote2 0x04
#define kFlagNote3 0x08
#define kFlagFlipped 0x10

#define kAllScoreFlags 0x0F
#define kAllFlags 0x1F

#define kScoreOffset 5

/**
 * Each character in the array is layed out as an LSB bitfield where:
 *  - Bits 0-3 are flags that indicate which notes the card has (positon
 *      corresponding to marked value) (1 is marked)
 *  - Bit 4 is a flag which marks if the card has been flipped (1) or 
 *      not
 *  - Bits 5 & 6 are a 2 bit unsigned integer, accessed by a shift by 
 *      kScoreOffset
 */
struct board_s {
    unsigned char** data;
    size_t nCols;
    size_t nRows;
};

//============================<Allocation>============================//
/**
 * Creates an empty board of default size
 */
board_t makeBoardDef() {
    return makeBoard(kDefBoardWidth, kDefBoardHeight);
}

/**
 * Creates an empty board of arbitrary size
 */
board_t makeBoard(size_t nCols, size_t nRows) {
    board_t board = malloc(sizeof(struct board_s));
    if(board == NULL) {
        return NULL;
    }
        
    board->nCols = nCols;
    board->nRows = nRows;
    
    board->data = calloc(nRows, sizeof(char*));
    if(board->data == NULL) {
        delBoard(board);
        return NULL;
    }
    
    for(size_t row = 0; row < nRows; row++){
        board->data[row] = calloc(nCols, sizeof(char));
        if(board->data[row] == NULL) {
            delBoard(board);
            return NULL;
        }
    }
    
    return board;
}

void delBoard(board_t board) {
    if(board == NULL)
        return;
    
    if(board->data != NULL) {
        for(size_t i = 0; i < board->nRows; i++) {
            if(board->data[i] != NULL)
                free(board->data[i]);
        }
        free(board->data);
    }
    
    free(board);
}

//==========================<Initialization>==========================//
void randInit(board_t board) {
    if(board == NULL)
        return;
    
    for(size_t row = 0; row < board->nRows; row++) {
        for(size_t col = 0; col < board->nCols; col++) {
            board->data[row][col] = (board->data[row][col] & kAllFlags) 
                                    + ((rand()%4) << kScoreOffset);
        }
    }
}

void setScore(board_t board, char score, size_t row, size_t col) {
    board->data[row][col] = (board->data[row][col] & kAllFlags) 
                            + ((score%kMaxScore) << kScoreOffset);
}

//==========================<Note Handling>===========================//
/**
 * Returns the bitfield of the notes in the particular cell. Any LSB 
 * bits 0-3 that have been set indicate the card is marked for those 
 * values.
 */
char getNotes(board_t board, size_t row, size_t col) {
    if(board == NULL || row >= board->nRows || col >= board->nCols) {
        return 0;
    }
    
    return board->data[row][col] & kAllScoreFlags;
}

/**
 * Sets the note for score 'val' on the specified card
 */
void addNote(board_t board, char val, size_t row, size_t col) {
    if(board == NULL || val < 0 || val >= kMaxScore || 
            row >= board->nRows || col >= board->nCols) {
        return;
    }
    
    char flag = 0;
    switch(val){    // Grab the flag to toggle
        case 0:
            flag = kFlagNote0;
            break;
        case 1:
            flag = kFlagNote1;
            break;
        case 2:
            flag = kFlagNote2;
            break;
        case 3:
            flag = kFlagNote3;
            break;
    }
    
    board->data[row][col] = board->data[row][col] ^ flag;
}

//==========================<Flip Controls>===========================//
/**
 * Invert the flipped state of this card
 */
void flipCard(board_t board, size_t row, size_t col) {
    if(board == NULL || row >= board->nRows || col >= board->nCols)
        return;
    
    board->data[row][col] = board->data[row][col] | kFlagFlipped;
}

void revealBoard(board_t board) {
    if(board == NULL)
        return;
    
    for(size_t row = 0; row < board->nRows; row++) {
        for(size_t col = 0; col < board->nCols; col++) {
            board->data[row][col] = board->data[row][col] | kFlagFlipped; //Set the flipped flag on each
        }
    }
}

/**
 * Returns true if this card is turned up
 */
bool isFlipped(board_t board, size_t row, size_t col) {
    if(board == NULL || row >= board->nRows || col >= board->nCols)
        return false;
    
    return (board->data[row][col] & kFlagFlipped) ? true : false;
    
}

//===========================<State Query>============================//
int getScore(board_t board, size_t row, size_t col) {
    if(board == NULL || row >= board->nRows || col >= board->nCols) {
        return 0;
    }
    return board->data[row][col]>>kScoreOffset;
    
}

size_t getNRows(board_t board) {
    if(board == NULL) 
        return 0;
    return board->nRows;
}

size_t getNCols(board_t board) {
    if(board == NULL) 
        return 0;
    return board->nCols;
}

