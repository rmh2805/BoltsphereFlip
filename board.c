#include "board.h"

#define kDefBoardWidth 5
#define kDefBoardHeight 5

#define kMaxScore 4

#define kFlagNote0 0x1
#define kFlagNote1 0x2
#define kFlagNote2 0x4
#define kFlagNote3 0x8
#define kFlagFlipped 0x10
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

//===========================<State Query>============================//
int getScore(board_t board, size_t row, size_t col) {
    if(board == NULL || row >= board->nRows || col >= board->nCols) {
        return -1;
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

