#ifndef  _CURSES_DISP_H_
#define  _CURSES_DISP_H_

#include <stdlib.h>
#include <stdio.h>
#include <ncurses.h>

#include "board.h"

/**
 * Provided for parity with other display code, always returns success
 */
int cursesDispInit();

/**
 * Provided for parity with other display code
 */
void cursesDispClose();

/**
 * Prints the board to stdout
 */
void cursesDispBoard(board_t board);

/**
 * Prints a help message and then halts for input
 */
void cursesDispHelp(char help, char note, char flip, char quit);

/**
 * Prints a status indicator 
 */
void cursesDispStatus(size_t score, size_t nRemain, const char * msg);

/**
 * Gets a command from stdin, puts it into buf
 */
void cursesGetCmd(char * buf, size_t bufSize);

#endif //_CURSES_DISP_H_
