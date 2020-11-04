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
    size_t lCardPos = centerCardPos - ((int)(nCols/2)) * (kCardWidth+1); 

    // Add the width and spacer offset to the leftmost position 
    return lCardPos + col * (kCardWidth + 1);
}

/**
 *  Converts the card row into the screen row
 */
size_t getCardRow(size_t row, size_t nRows) {
    if(screenHeight == 0) //Ensure initialization
        return 0;

    size_t centerCardPos = screenHeight / 2 - kCardHeight/2;  //Center card in card col nRows/2

    // Subtract the height of the (nRows/2 - 1) cards above and their spacers from the
    // center position
    size_t tCardPos = centerCardPos - ((int)(nRows/2)) * (kCardHeight+1); 

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
    
    refresh();
    return EXIT_SUCCESS;    //Stub this out for now
}


void cursesDispClose() {
    endwin();
}

void cDispCell(board_t board, size_t row, size_t col);
void cDispRowIndics(board_t board, size_t row);
void cDispColIndics(board_t board, size_t col);

void cursesDispBoard(board_t board) {
    if(board == NULL || screenWidth == 0 || screenHeight == 0) return;
    
    size_t boardCols = getNCols(board);
    size_t boardRows = getNRows(board);

    for(size_t row = 0; row < boardRows; row++) {
        for(size_t col = 0; col < boardCols; col++) {
            cDispCell(board, row, col);
            mvaddch(getCardRow(row, boardRows) - 1, getCardCol(col, boardCols) + kCardWidth/2, '|');
            mvaddch(getCardRow(row, boardRows) + kCardHeight/2, getCardCol(col, boardCols) - 1, '-');
            refresh();
        }
        mvaddch(getCardRow(row, boardRows) + kCardHeight/2, getCardCol(boardCols, boardCols) - 1, '-');
        cDispRowIndics(board, row);
    }
    
    for(size_t col = 0; col < boardCols; col++) {
        mvaddch(getCardRow(boardRows, boardRows) - 1, getCardCol(col, boardCols) + kCardWidth/2, '|');
        cDispColIndics(board, col);
    }

    refresh();

}

void cursesDispHelp(char help, char note, char flip, char quit) {

}

void cursesDispStatus(size_t score, size_t nRemain, const char * msg) {

}

void cursesGetCmd(char * buf, size_t bufSize) {

}

//=======================================<Helper Functions>=======================================//
void cDispFrame(size_t screenRow, size_t screenCol) {
    char buf[kCardWidth + 1];
    buf[kCardWidth] = 0;
    buf[0] = '+';
    buf[kCardWidth-1] = '+';
    for(size_t col = 1; col < kCardWidth-1; col++) {
        buf[col] = (col == kCardWidth/2) ? '+' : '-';
    }
    
    mvprintw(screenRow, screenCol, buf);
    mvprintw(screenRow + kCardHeight-1, screenCol, buf);
    
    buf[0] = '|';
    buf[kCardWidth - 1] = '|';
    for(size_t col = 1; col < kCardWidth-1; col++) {
        buf[col] = ' ';
    }
    for(size_t row = 1; row < kCardHeight-1; row++) {
        if(row == kCardHeight/2) {
            buf[0] = '+';
            buf[kCardWidth-1] = '+';
        }

        mvprintw(screenRow + row, screenCol, buf);

        if(row == kCardHeight/2) {
            buf[0] = '|';
            buf[kCardWidth-1] = '|';
        }
    }

}

void cDispRowIndics(board_t board, size_t row) {
    //Calculate the information for this row
    size_t totScore = 0;
    size_t nBombs = 0;
    
    size_t nCols = getNCols(board);

    for(size_t col = 0; col < nCols; col++) {
        size_t score = getScore(board, row, col);
        totScore += score;
        if(score == 0) ++nBombs;
    }

    //Do screen space calculations
    size_t lCol = getCardCol(0, nCols) - kCardWidth - 1;
    size_t rCol = getCardCol(nCols, nCols);
    size_t screenRow = getCardRow(row, getNRows(board));

    wattron(stdscr, COLOR_PAIR(kIndicatorPalette));

    //Print the frames
    cDispFrame(screenRow, lCol);
    cDispFrame(screenRow, rCol);

    //Print the row number in the left indicator
    mvaddch(screenRow + kCardHeight/2, lCol + kCardWidth/2, '0' + row + 1);

    refresh();
    wattroff(stdscr, COLOR_PAIR(kIndicatorPalette));
}

void cDispColIndics(board_t board, size_t col) {

}

void cDispCell(board_t board, size_t row, size_t col) {
    bool flipped = isFlipped(board, row, col);
    char notes = getNotes(board, row, col);
    int score = getScore(board, row, col);    

    int palette = kUnflippedPalette;
    if(flipped) {
        palette = (score) ? kFlippedPalette : kBombPalette;
    }
    
    //Do screen space calculations
    size_t screenCol = getCardCol(col, getNCols(board));
    size_t screenRow = getCardRow(row, getNRows(board));
    
    //Start printing
    wattron(stdscr, COLOR_PAIR(palette));
    
    //Print the card frame  
    cDispFrame(screenRow, screenCol);
    
    //Print the score or the notes
    if(flipped) {
        mvprintw(screenRow + kCardHeight/2, screenCol + kCardWidth/2, "%d", score);
    } else {
        //Print the card back
        for(size_t row = 1; row < kCardHeight-1; row++) {
            mvaddch(screenRow + row, screenCol + kCardWidth/2, '|');
        }
        
        for(size_t col = 1; col < kCardWidth-1; col++) {
            mvaddch(screenRow + kCardHeight/2, screenCol + col, (col == kCardWidth/2) ? '+' : '-');
        }

        //Print whichever notes are present
        if(notes & 0x01) 
            mvaddch(screenRow + kCardHeight/4, screenCol + kCardWidth/4, '0');
        if(notes & 0x02)
            mvaddch(screenRow + kCardHeight/4, screenCol + kCardWidth*3/4, '1');
        if(notes & 0x04)
            mvaddch(screenRow + kCardHeight*3/4, screenCol + kCardWidth/4, '2');
        if(notes & 0x08)
            mvaddch(screenRow + kCardHeight*3/4, screenCol + kCardWidth*3/4, '3');

    }

    refresh();
    wattroff(stdscr, COLOR_PAIR(palette));
}
