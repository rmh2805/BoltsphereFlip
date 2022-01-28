#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

#include "dispBase.h"
#include "dispPrint.h"
#include "dispCurses.h"

#define kInBufSize 64
const disp_t(* mkDisp)() = mkPrintDisp;

int main() {
    //=======================<Declare State to Cleanup>=======================//
    int status = EXIT_FAILURE;

    disp_t disp;
    bool dispInit = false;

    dispBuf_t buf;
    bool bufInit = false;

    char inBuf[kInBufSize];

    //============================<Initialization>============================//
    // Basic display
    disp = mkDisp();
    if(disp.init(&disp.data) < 0) goto testDisp_fail;
    dispInit = true;

    // Get display size for buffer init
    size_t scrRows = 0, scrCols = 0;
    disp.getScrSize(disp.data, &scrRows, &scrCols);

    // Display Buffer
    buf = mkDispBuf(scrRows, scrCols);
    if(buf.data == NULL) goto testDisp_fail;
    bufInit=true;

    //================================<Tests>=================================//
    // Test Output
    disp.printText(disp.data, "OUTPUT TESTS", kWhitePalette, scrRows/2, scrCols/2-6);

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