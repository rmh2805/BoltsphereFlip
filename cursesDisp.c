#include "cursesDisp.h"

//======================================<Display Constants>=======================================//
#define kCardWidth 5
#define kCardHeight 5

static size_t screenWidth = 0;
static size_t screenHeight = 0;

//======================================<Palette Constants>======================================//
#define kBasePalette 0
#define kIndicatorPalette 1
#define kUnflippedPalette 2
#define kFlippedPalette 3
#define kBombPalette 4

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
int cursesDispInit(board_t board) {
    if(board == NULL) return EXIT_FAILURE;

    initscr(); //start curses mode
    
    // Check screen size
    getmaxyx(stdscr, screenHeight, screenWidth);
    
    size_t boardRows = getNRows(board);
    size_t boardCols = getNCols(board);
    
    if((boardRows + 2) * kCardHeight + boardRows - 1 > screenHeight ||
            (boardCols + 2) * kCardWidth + boardCols - 1 > screenWidth) {
        endwin();
        printf("Error: Console window too small\n");
        return EXIT_FAILURE;
    }

    // Assign color palettes
    if(!has_colors()) {
        endwin();
        printf("Error: Console does not support color\n");
        return EXIT_FAILURE;
    }

    start_color();
    init_pair(kIndicatorPalette, COLOR_BLACK, COLOR_WHITE);
    init_pair(kUnflippedPalette, COLOR_WHITE, COLOR_BLUE);
    init_pair(kFlippedPalette, COLOR_BLACK, COLOR_GREEN);
    init_pair(kBombPalette, COLOR_WHITE, COLOR_RED);
    
    return EXIT_SUCCESS;    //Stub this out for now
}


void cursesDispClose() {
    endwin();
}

void printCell(board_t board, size_t row, size_t col);
void printRowIndics(board_t board, size_t row);
void printColIndics(board_t board, size_t col);

void cursesDispBoard(board_t board) {
    if(board == NULL || screenWidth == 0 || screenHeight == 0) return;
    
    size_t boardWidth = getNCols(board);
    size_t boardHeaith = getNRows(board);

    for(size_t row = 0; row < boardWidth; row++) {
        for(size_t col = 0; col < boardHeight; col++) {
            printCell(board, row, col);
        }
    }

}

void cursesDispHelp(char help, char note, char flip, char quit) {

}

void cursesDispStatus(size_t score, size_t nRemain, const char * msg) {

}

void cursesGetCmd(char * buf, size_t bufSize) {

}

//=======================================<Helper Functions>=======================================//
void printCell(board_t board, size_t row, size_t col) {
    
}

void printRowIndics(board_t board, size_t row) {

}

void printColIndics(board_t board, size_t col) {

}

