#include "dispPrint.h"

//============================<Declare Disp Impls>============================//
int     print_init         (void** data);
int     print_close        (void* data);
void    print_printText    (void * data, const char * str, short palette, size_t row, size_t col);
int     print_printBuf     (void * data, dispBuf_t buf);
void    print_clearScr     (void* data);
int     print_getCh        (void* data);
void    print_getStr       (void* data, char* buf, size_t nBuf);
void    print_getScrSize   (void* data, size_t* rows, size_t* cols);

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

    disp.monoDisp = true;
    disp.data = NULL;

    return disp;
}

//================================<Disp Impls>================================//
int print_init (void** data){
    data = data;
    return 0;
}

int print_close (void* data){
    data = data;
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
    if(buf.data == NULL) return -1;
    data = data;

    for(size_t row = 0; row < buf.screenRows; ++row) {
        for(size_t col = 0; col < buf.screenCols; ++col) {
            char ch = buf.data[row][col].ch;
            printf("%c", (charPrintable(ch)) ? ch : ' ');
        }
        printf("\n");
    }
    return 0;
}

void print_clearScr (void* data){
    data = data;

    for(int i = 0; i < kDefPrintDisplyRows; ++i) {
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
    data = data;

    *rows = kDefPrintDisplyRows;
    *cols = kDefPrintDisplayCols;
}
