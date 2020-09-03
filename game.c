#include <stdlib.h> 
#include <stdio.h>  //printf(), fprintf()
#include <time.h>   //time()

#include "printDisp.h"
#include "board.h"

int main() {
    //Initialize the random number generator for board population
    unsigned int mySeed = (unsigned int) time(NULL);
    srand(mySeed);
    
    //Allocate the board, exit on failure
    board_t board = makeBoardDef();
    if(board == NULL) {
        fprintf(stderr, "Failed to allocate the board, exit failure");
        return EXIT_FAILURE;
    }
    
    randInit(board);
    
    //Main Loop here
    
    
    //Delete the board and exit successfully
    delBoard(board);
    return EXIT_SUCCESS;
}

