#ifndef _DISP_CURSES_H_
#define _DISP_CURSES_H_

#include <stdlib.h>
#include <stdbool.h>
#include <curses.h>

#include "dispBase.h"

//==========================<Display Interface Hook>==========================//
/**
 * @brief Generates an nCurses display interface
 * 
 * @return An nCurses display interface
 */
disp_t mkCursesDisp();

#endif