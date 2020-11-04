#include <stdlib.h>
#include <stdio.h>
#include <time.h>

#include "board.h"
#include "cursesDisp.h"

int main() {
    //========================================<Allocation>========================================//
    board_t board = makeBoardDef();
    if(board == NULL) {
        fprintf(stderr, "Failed to allocate the board, exit failure\n");
        return EXIT_FAILURE;
    }

    if(cursesDispInit(board) != EXIT_SUCCESS) {
        delBoard(board);
        fprintf(stderr, "Failed to initialize the curses display, exit failure\n");
        return EXIT_FAILURE;
    }

    srand((unsigned int) time(NULL));   //Initialize rng for board
    randInit(board);    //Initialize the board with random scores

    //========================================<Main Code>=========================================//

    //=========================================<Cleanup>==========================================//
    delBoard(board);
    cursesDispClose();
    return EXIT_SUCCESS;
}
