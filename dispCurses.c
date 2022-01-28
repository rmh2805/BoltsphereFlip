#include "dispCurses.h"

//============================<Declare Disp Impls>============================//
int     curses_init         (void** data);
int     curses_close        (void* data);
void    curses_printText    (void * data, const char * str, short palette, size_t row, size_t col);
int     curses_printBuf     (void * data, dispBuf_t buf);
void    curses_clearScr     (void* data);
int     curses_getCh        (void* data);
void    curses_getStr       (void* data, char* buf, size_t nBuf);
void    curses_getScrSize   (void* data, size_t* rows, size_t* cols);

//============================<Exposed Functions>=============================//
disp_t mkCursesDisp() {
    disp_t disp = mkNullDisp();

    disp.init = curses_init;
    disp.close = curses_close;
    disp.printText = curses_printText;
    disp.printBuf = curses_printBuf;
    disp.clearScr = curses_clearScr;
    disp.getCh = curses_getCh;
    disp.getStr = curses_getStr;
    disp.getScrSize = curses_getScrSize;

    disp.monoDisp = false;
    disp.data = NULL;

    return disp;
}

//================================<Disp Impls>================================//
int curses_init (void** data){
    return -1;
}

int curses_close (void* data){
    return -1;
}

void curses_printText (void * data, const char * str, short palette, size_t row, size_t col) {

}

int curses_printBuf (void * data, dispBuf_t buf){
    return -1;
}

void curses_clearScr (void* data){

}

int curses_getCh (void* data){
    return -1;
}

void curses_getStr (void* data, char* buf, size_t nBuf){
}

void curses_getScrSize (void* data, size_t* rows, size_t* cols){

}
