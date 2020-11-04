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

void cDispCell(board_t board, size_t row, size_t col) {
    //Calculate the palette for this card
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

    //Prepare the buffer
    char buf[kCardWidth + 1];
    buf[kCardWidth] = 0;

    //Print the upper and lower borders
    buf[0] = '+';
    for(size_t col = 1; col < kCardWidth - 1; col++) {
        buf[col] = (col == kCardWidth/2) ? '+' : '-';
    }
    buf[kCardWidth - 1] = '+';
    
    wattron(stdscr, COLOR_PAIR(palette));  
    mvprintw(screenRow, screenCol, buf);
    mvprintw(screenRow + kCardHeight - 1, screenCol, buf);

    buf[0] = '|';
    buf[kCardWidth-1] = '|';
    for(size_t row = 1; row < kCardHeight - 1; row++) {
        if(row == kCardHeight/2) {
            buf[0] = '+';
            buf[kCardWidth - 1] = '+';
        }

        for(size_t col = 1; col < kCardWidth - 1; col++) {
            if(!flipped) {
                if(row == kCardHeight/2) {
                    buf[col] = (col == kCardWidth/2) ? '+' : '-';
                } else if (row == kCardHeight / 4) {
                    if(col == kCardWidth / 4) buf[col] = (notes & 0x01) ? '0' : ' ';
                    else if(col == 3 * kCardWidth / 4) buf[col] = (notes & 0x02) ? '1' : ' ';
                } else if (row == 3 * kCardHeight / 4) {
                    if(col == kCardWidth / 4) buf[col] = (notes & 0x04) ? '2' : ' ';
                    else if(col == 3 * kCardWidth / 4) buf[col] = (notes & 0x08) ? '3' : ' '; 
                } else {
                    buf[col] = ' ';
                }
                
                if(col == kCardWidth/2) buf[col] = (row == kCardHeight/2) ? '+' : '|';

            } else {
                buf[col] = (col == kCardWidth/2 && row == kCardHeight/2) ? '0' + score : ' ';
            }
        }
        
        mvprintw(screenRow + row, screenCol, buf);
        if(row == kCardHeight/2) {
             buf[0] = '|';
             buf[kCardWidth-1] = '|';
        }


    }


    refresh();
    wattroff(stdscr, COLOR_PAIR(palette));
}

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
void cDispRowIndics(board_t board, size_t row) {

}

void cDispColIndics(board_t board, size_t col) {

}

