#include <stdlib.h> 
#include <stdbool.h>
#include <stdio.h>  //printf(), fprintf()
#include <time.h>   //time()

#include "printDisp.h"
#include "board.h"

#define kBufSize 64

#define kHelpChar '?'
#define kNoteChar '#'
#define kFlipChar '!'

typedef struct dispFunc_s {
    int (* InitDisp)();
    void (*CloseDisp)();

    void (* DispHelp)(char help, char note, char flip);
    void (* DispStatus)(size_t score, size_t nRemain, const char * msg);
    void (* DispBoard)(board_t board);

    void (* GetCmd)(char * buf, size_t bufSize);
} DispFunc;

int main() {
    //======================================<Initialization>======================================//
    //===================================<Heap Allocation>====================================//
    board_t board = makeBoardDef();
    if(board == NULL) {
        fprintf(stderr, "Failed to allocate the board, exit failure\n");
        return EXIT_FAILURE;
    }
    
    char* buf = calloc(kBufSize, sizeof(char));
    if(buf == NULL) {
        delBoard(board);
        fprintf(stderr, "Failed to allocate the buffer, exit failure\n");
        return EXIT_FAILURE;
    }

    //====================================<Initialization>====================================//
    srand((unsigned int) time(NULL)); //Initialize RNG
    randInit(board); // Randomly populate the board with scores
    
    //Grab the board dimensions once
    size_t nRows = getNRows(board);
    size_t nCols = getNCols(board);
    
    size_t score = 1;   // Variable to track the score

    //Count the number of required tiles (score greater than 1)
    size_t requiredTiles = 0;
    for(size_t row = 0; row < nRows; row++) {
        for(size_t col = 0; col < nCols; col++) {
            requiredTiles += (getScore(board, row, col) > 1) ? 0 : 1;
        }
    }
    
    // Set the display functions (here's where swapping will occur)
    DispFunc dispFunc;
    dispFunc.InitDisp = printDispInit;
    dispFunc.CloseDisp = printDispClose;
    dispFunc.DispHelp = printDispHelp;
    dispFunc.DispStatus = printDispStatus;
    dispFunc.DispBoard = printDispBoard;
    dispFunc.GetCmd = printGetCmd;

    if(dispFunc.InitDisp() != EXIT_SUCCESS) {
        delBoard(board);
        free(buf);
        fprintf(stderr, "Failed to initialize the display, exit failure\n");
        return EXIT_FAILURE;
    }
    
    //========================================<Main Code>=========================================//
    dispFunc.DispHelp(kHelpChar, kNoteChar, kFlipChar);

    while(score > 0 && requiredTiles > 0) { //Repeat until flipped a 0 or all required tiles
        dispFunc.DispStatus(score, requiredTiles, "Welcome to boltsphere flip!");
        dispFunc.DispBoard(board);
        dispFunc.GetCmd(buf, kBufSize);
        break; //Just for now
    }

    //=========================================<Cleanup>==========================================//
    delBoard(board);
    free(buf);
    return EXIT_SUCCESS;
}

