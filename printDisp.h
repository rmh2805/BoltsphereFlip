#ifndef  _PRINT_DISP_H_
#define  _PRINT_DISP_H_

#include <stdlib.h>
#include <stdio.h>

#include "board.h"

/**
 * Provided for parity with other display code, always returns success
 */
int printDispInit();

/**
 * Provided for parity with other display code
 */
void printDispClose();

/**
 * Prints the board to stdout
 */
void printDispBoard(board_t board);

/**
 * Prints a help message and then halts for input
 */
void printDispHelp(char help, char note, char flip, char quit);

/**
 * Prints a status indicator 
 */
void printDispStatus(size_t score, size_t nRemain, const char * msg);

/**
 * Gets a command from stdin, puts it into buf
 */
void printGetCmd(char * buf, size_t bufSize);

#endif //_PRINT_DISP_H_
