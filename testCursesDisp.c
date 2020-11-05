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
    
    addNote(board, 0, 0, 0);
    addNote(board, 1, 0, 1);
    addNote(board, 2, 0, 2);
    addNote(board, 3, 0, 3);
    addNote(board, 1, 0, 4);
    addNote(board, 2, 0, 4);
    
    flipCard(board, 1, 0);
    flipCard(board, 1, 1);

    //========================================<Main Code>=========================================//
    cursesDispBoard(board);
    
    char buf[1024];
    cursesGetCmd(true, buf, 1024);
    
    cursesDispHelp('?', '#', '!', '`');
    
    revealBoard(board);
    cursesDispBoard(board);
    cursesDispStatus(1, 2, buf);
    mvgetch(0, 0);

    //=========================================<Cleanup>==========================================//
    delBoard(board);
    cursesDispClose();
    return EXIT_SUCCESS;
}
