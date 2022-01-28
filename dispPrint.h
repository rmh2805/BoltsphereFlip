#ifndef _PRINT_DISP_H_
#define _PRINT_DISP_H_

#include <stdlib.h>
#include <stdbool.h>

#include <stdio.h>

#include "dispBase.h"

#define kDefPrintDisplyRows 50
#define kDefPrintDisplayCols 80

/**
 * @brief Generates a stdio based display interface
 * 
 * @return A stdio based display interface
 */
disp_t mkPrintDisp();

#endif