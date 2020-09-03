#include <stdlib.h> 
#include <stdio.h>  //printf(), fprintf()
#include <time.h>   //time()

#include "printDisp.h"
#include "board.h"

#define kBufSize 64

int main() {
    //Initialize the random number generator for board population
    unsigned int mySeed = (unsigned int) time(NULL);
    srand(mySeed);
    
    //Allocate the board, exit on failure
    board_t board = makeBoardDef();
    if(board == NULL) {
        fprintf(stderr, "Failed to allocate the board, exit failure\n");
        return EXIT_FAILURE;
    }
    
    //Allocate the input buffer
    char* buf = calloc(kBufSize, sizeof(char));
    if(buf == NULL) {
        delBoard(board);
        fprintf(stderr, "Failed to allocate the buffer, exit failure\n");
        return EXIT_FAILURE;
    }
    
    randInit(board);
    
    //Main Loop here
    
    
    //Free all heap memory and exit successfully
    delBoard(board);
    free(buf);
    return EXIT_SUCCESS;
}

