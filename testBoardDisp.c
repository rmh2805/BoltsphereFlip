#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

#include "board.h"

#include "dispBase.h"
#include "dispPrint.h"
#include "boardDisp.h"

int main() {
    int status = EXIT_FAILURE;
    
    disp_t disp;
    bool dispInit = false;

    dispBuf_t dispBuf;
    bool dispBufInit = false;

    //============================<Initialization>============================//
    // Initialize the display
    disp = mkPrintDisp();
    if(disp.init(&disp.data) < 0) goto testBoardDisp_fail;
    size_t scrRows = 0, scrCols = 0;
    disp.getScrSize(disp.data, &scrRows, &scrCols);

    // Initialize the display buffer


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

    return status;
}