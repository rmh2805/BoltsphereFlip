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
    
    randInit(board);    // Initialize scores
    
    //Grab the dimensions once
    size_t nRows = getNRows(board);
    size_t nCols = getNCols(board);
    
    //Count the number of required tiles (score greater than 1)
    size_t requiredTiles = 0;
    for(size_t row = 0; row < nRows; row++) {
        for(size_t col = 0; col < nCols; col++) {
            requiredTiles += (getScore(board, row, col) > 1) ? 0 : 1;
        }
    }
    
    
    long score = 1;   // Variable to track the score
    
    //Main Loop here
    
    while(score > 0 && requiredTiles > 0) {
        
    }
    
    //Free all heap memory and exit successfully
    delBoard(board);
    free(buf);
    return EXIT_SUCCESS;
}

