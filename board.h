#ifndef  _BOARD_H_
#define  _BOARD_H_

#include <stdlib.h>
#include <stdbool.h>

typedef struct board_s * board_t;

board_t makeBoardDef();
board_t makeBoard(size_t nCols, size_t nRows);
void rmBoard(board_t board);

#endif //_BOARD_H_
