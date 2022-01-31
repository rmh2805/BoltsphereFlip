#include "dispPrint.h"

#ifndef min
#define min(a,b) ((b<a) ? b : a)
#endif

//==============================<Internal Data>===============================//
typedef struct printData_s {
    size_t scrRows;
    size_t scrCols;
} printData_t;

printData_t* mkPrintData() {
    return calloc(1, sizeof(printData_t));
}

void rmPrintData(printData_t* printData) {
    if(printData == NULL) return;
    free(printData);
}

//============================<Declare Disp Impls>============================//
int     print_init          (void** data);
int     print_close         (void* data);
void    print_printText     (void * data, const char * str, short palette, size_t row, size_t col);
int     print_printBuf      (void * data, dispBuf_t buf);
void    print_clearScr      (void* data);
int     print_getCh         (void* data);
void    print_getStr        (void* data, char* buf, size_t nBuf);
void    print_getScrSize    (void* data, size_t* rows, size_t* cols);
int    print_setScrSize    (void* data, size_t rows, size_t cols);

//============================<Exposed Functions>=============================//
disp_t mkPrintDisp() {
    disp_t disp = mkNullDisp();

    disp.init = print_init;
    disp.close = print_close;
    disp.printText = print_printText;
    disp.printBuf = print_printBuf;
    disp.clearScr = print_clearScr;
    disp.getCh = print_getCh;
    disp.getStr = print_getStr;
    disp.getScrSize = print_getScrSize;
    disp.setScrSize = print_setScrSize;

    disp.monoDisp = true;
    disp.data = NULL;

    return disp;
}

//================================<Disp Impls>================================//
int print_init (void** data){
    if(data == NULL) {
        return -1;
    }

    printData_t* printData = mkPrintData();
    if(printData == NULL) return -1;

    printData->scrRows = kDefPrintDisplayRows;
    printData->scrCols = kDefPrintDisplayCols;
    return 0;
}

int print_close (void* data){
    rmPrintData((printData_t*)data);
    return 0;
}

void print_printText (void * data, const char * str, short palette, size_t row, size_t col) {
    data = data;
    palette = palette;
    row = row;

    for(size_t i = 0; i < col; ++i) {
        printf(" ");
    }
    printf("%s\n", str);
}

int print_printBuf (void * data, dispBuf_t buf){
    if(buf.data == NULL || data == NULL) return -1;
    printData_t* printData = (printData_t*) data;

    size_t maxRow = min(buf.screenRows, printData->scrRows);
    size_t maxCol = min(buf.screenCols, printData->scrCols);

    for(size_t row = 0; row < maxRow; ++row) {
        for(size_t col = 0; col < maxCol; ++col) {
            char ch = buf.data[row][col].ch;
            printf("%c", (charPrintable(ch)) ? ch : ' ');
        }
        printf("\n");
    }
    return 0;
}

void print_clearScr (void* data){
    if(data == NULL) return;
    printData_t* printData = (printData_t*) data;

    for(size_t i = 0; i < printData->scrRows; ++i) {
        printf("\n");
    }
}

int print_getCh (void* data){
    data = data;
    return getchar();
}

void print_getStr (void* data, char* buf, size_t nBuf){
    if(buf == NULL || nBuf == 0) return;
    data = data;

    fgets(buf, nBuf, stdin);
}

void print_getScrSize (void* data, size_t* rows, size_t* cols){
    if(data == NULL) {
        return;
    }
    printData_t* printData = (printData_t*) data;

    if(rows != NULL) *rows = printData->scrRows;
    if(cols != NULL) *cols = printData->scrCols;
}

int print_setScrSize (void* data, size_t rows, size_t cols) {
    if(data == NULL) return -1;
    printData_t* printData = (printData_t*) data;

    if(rows != 0) printData->scrRows = rows;
    if(cols != 0) printData->scrCols = cols;

    return 0;
}
