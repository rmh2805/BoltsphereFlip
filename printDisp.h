#ifndef  _PRINT_DISP_H_
#define  _PRINT_DISP_H_

#include <stdlib.h>
#include <stdio.h>

#include "board.h"

int printDispInit();

void printDispBoard(board_t board);
void printDispHelp(char help, char note, char flip);
void printDispStatus(size_t score, size_t nRemain, const char * msg);

void printGetCmd(char * buf, size_t bufSize);

#endif //_PRINT_DISP_H_
