#include "board.h"

#define kDefBoardWidth 5
#define kDefBoardHeight 5

#define kFlagNote0 0x1
#define kFlagNote1 0x2
#define kFlagNote2 0x4
#define kFlagNote3 0x8
#define kFlagFlipped 0x10

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

board_t makeBoardDef() {
    return makeBoard(kDefBoardWidth, kDefBoardHeight);
}

board_t makeBoard(size_t nCols, size_t nRows) {
    return NULL;
}

void rmBoard(board_t board) {
    if(board == NULL)
        return;
    
    if(board->data != NULL) {
        
    }
    
    free(board);
}
