#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

#include "board.h"

#include "dispBase.h"
#include "dispPrint.h"
#include "boardDisp.h"

#ifndef max
#define max(a,b) ((b > a) ? b : a)
#endif

#define kErrorBufferSize 128

int main() {
    int status = EXIT_FAILURE;
    char errorBuffer[kErrorBufferSize];
    char* exitMsg = NULL;

    disp_t disp;
    bool dispInit = false;

    dispBuf_t dispBuf;
    bool dispBufInit = false;

    board_t board;
    bool boardInit = false;

    //============================<Initialization>============================//
    // Initialize the display
    disp = mkPrintDisp();
    if(disp.init(&disp.data) < 0) {
        sprintf(errorBuffer, "*FATAL ERROR* Failed to init display\n");
        exitMsg = errorBuffer;
        goto testBoardDisp_fail;
    }
    dispInit = true;

    // Initialize the board
    if((board = makeBoardDef()) == NULL) {
        sprintf(errorBuffer, "*FATAL ERROR* Failed to init the board\n");
        exitMsg = errorBuffer;
        goto testBoardDisp_fail;
    }
    boardInit = true;

    // Get the minimum screen/buffer size to display the board
    size_t minRows = 0, minCols = 0;
    boardMinBufSize(board, &minRows, &minCols);

    // Try to set the display size to at least that min
    size_t scrRows = 0, scrCols = 0;
    disp.getScrSize(disp.data, &scrRows, &scrCols);
    if(disp.setScrSize != NULL) {
        disp.setScrSize(disp.data, max(scrRows, minRows), max(scrCols, minCols));
    }

    // Check if the screen can fit the board
    disp.getScrSize(disp.data, &scrRows, &scrCols);
    if(scrRows < minRows || scrCols < minCols) {
        sprintf(errorBuffer, "*FATAL ERROR* The screen is too small for the board\n");
        exitMsg = errorBuffer;
        goto testBoardDisp_fail;
    }

    // Allocate the display buffer
    dispBuf = mkDispBuf(scrRows, scrCols);
    if(dispBuf.data == NULL) {
        sprintf(errorBuffer, "*FATAL ERROR* Failed to allocate the display buffer\n");
        exitMsg = errorBuffer;
        goto testBoardDisp_fail;
    }

    //==============================<Run Tests>===============================//

    //===========================<Cleanup and Exit>===========================//
    status = EXIT_SUCCESS;
testBoardDisp_fail:
    if(dispInit) {
        disp.close(disp.data);
    }

    if(dispBufInit) {
        rmDispBuf(dispBuf);
    }

    if(boardInit) {
        delBoard(board);
    }

    if(exitMsg != NULL) {
        printf("%s", exitMsg);
    }

    return status;
}