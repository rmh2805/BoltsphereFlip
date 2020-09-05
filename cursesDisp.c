#include "cursesDisp.h"

#define kMaxBoardDim 5

#define kCardWidth 5
#define kCardHeight 5

size_t screenWidth = 0;
size_t screenHeight = 0;

//===========================================<Helpers>============================================//
/**
 *  Converts the card column into the screen column
 */
size_t getCardCol(size_t col, size_t nCols) {
    if(screenWidth == 0)
        return 0;

    size_t centerCardPos = screenWidth / 2 - kCardWidth/2;  //Center card in col card nCols/2

    // Subtract the width of the (nCols/2 - 1) cards to the left and their spacers from the
    // center position
    size_t lCardPos = centerCardPos - ((int)(nCols/2)-1) * (kCardWidth+1); 

    // Add the width and spacer offset to the leftmost position 
    return lCardPos + col * (kCardWidth + 1);
}

/**
 *  Converts the card row into the screen row
 */
size_t getCardRow(size_t row, size_t nRows) {
    if(screenHeight == 0) //Ensure initialization
        return 0;

    size_t centerCardPos = screenWidth / 2 - kCardHeight/2;  //Center card in card col nRows/2

    // Subtract the height of the (nRows/2 - 1) cards above and their spacers from the
    // center position
    size_t tCardPos = centerCardPos - ((int)(nRows/2)-1) * (kCardHeight+1); 

    // Add the height and spacer offset to the topmost position 
    return tCardPos + row * (kCardHeight + 1);
}



//===========================================<Exposed>============================================//
int cursesDispInit() {
    return EXIT_FAILURE;    //Stub this out for now
}


void cursesDispClose() {

}

void cursesDispBoard(board_t board) {

}

void cursesDispHelp(char help, char note, char flip, char quit) {

}

void cursesDispStatus(size_t score, size_t nRemain, const char * msg) {

}

void cursesGetCmd(char * buf, size_t bufSize) {

}
