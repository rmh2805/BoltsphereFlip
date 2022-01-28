#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

#include "dispBase.h"
#include "dispPrint.h"
#include "dispCurses.h"

#define kBufSize 64
disp_t(* mkDisp)() = mkPrintDisp;

int main() {
    //=======================<Declare State to Cleanup>=======================//
    int status = EXIT_FAILURE;

    disp_t disp;
    bool dispInit = false;

    dispBuf_t buf;
    bool bufInit = false;

    char inBuf[kBufSize];
    char outBuf[kBufSize];

    //============================<Initialization>============================//
    // Basic display
    disp = mkDisp();
    if(disp.init(&disp.data) < 0) {
        fprintf(stderr, "*FATAL ERROR*: failed to initialize the display\n");
        goto testDisp_fail;
    }
    dispInit = true;

    // Get display size for buffer init
    size_t scrRows = 0, scrCols = 0;
    disp.getScrSize(disp.data, &scrRows, &scrCols);

    // Display Buffer
    buf = mkDispBuf(scrRows, scrCols);
    if(buf.data == NULL) {
        fprintf(stderr,"*FATAL ERROR*: Failed to initialize the display buffer\n");
        goto testDisp_fail;
    }
    bufInit=true;

    //================================<Tests>=================================//
    // Test Basic IO
    disp.printText(disp.data, "Basic Tests (1/2) (printText): Can you see me?", 
                    kWhitePalette, 0, 0);

    disp.printText(disp.data, "Basic Tests (2/2) (getStr): Enter any text", 
                    kWhitePalette, 1, 0);
    disp.getStr(disp.data, inBuf, kBufSize);
    disp.printText(disp.data, "Got String:", kDefPalette, 2, 0);
    disp.printText(disp.data, inBuf, kDefPalette, 2, 12);

    disp.printText(disp.data, "Press Enter to Continue", kDefPalette, scrRows-1, 0);
    disp.getStr(disp.data, inBuf, kBufSize);

    //===========================<Cleanup and Exit>===========================//
    status = EXIT_SUCCESS;
testDisp_fail:
    if(dispInit) {
        disp.close(disp.data);
    }
    if(bufInit) {
        rmDispBuf(buf);
    }

    return status;
}