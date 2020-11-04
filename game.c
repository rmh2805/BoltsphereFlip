#include <stdlib.h> 
#include <stdbool.h>
#include <stdio.h>  //printf(), fprintf()
#include <time.h>   //time()
#include <string.h>

#include "cursesDisp.h"
#include "printDisp.h"
#include "board.h"

#define kBufSize 64

#define kHelpChar '?'
#define kNoteChar '#'
#define kFlipChar '!'
#define kQuitChar '~'

typedef struct dispFunc_s {
    int (* InitDisp)(board_t board);
    void (*CloseDisp)();

    void (* DispHelp)(char help, char note, char flip, char quit);
    void (* DispStatus)(size_t score, size_t nRemain, const char * msg);
    void (* DispBoard)(board_t board);

    void (* GetCmd)(char * buf, size_t bufSize);
} DispFunc;

int main() {
    //======================================<Initialization>======================================//
    //===================================<Heap Allocation>====================================//
    board_t board = makeBoardDef();
    if(board == NULL) {
        fprintf(stderr, "Failed to allocate the board, exit failure\n");
        return EXIT_FAILURE;
    }
    
    char* buf = calloc(kBufSize, sizeof(char));
    if(buf == NULL) {
        delBoard(board);
        fprintf(stderr, "Failed to allocate the buffer, exit failure\n");
        return EXIT_FAILURE;
    }

    //====================================<Initialization>====================================//
    srand((unsigned int) time(NULL)); //Initialize RNG
    randInit(board); // Randomly populate the board with scores
    
    //Grab the board dimensions once
    size_t nRows = getNRows(board);
    size_t nCols = getNCols(board);
    
    size_t score = 1;   // Variable to track the score

    //Count the number of required tiles (score greater than 1)
    size_t requiredTiles = 0;
    for(size_t row = 0; row < nRows; row++) {
        for(size_t col = 0; col < nCols; col++) {
            requiredTiles += (getScore(board, row, col) > 1) ? 1 : 0;
        }
    }
    
    // Set the display functions (here's where swapping will occur)
    DispFunc dispFunc;
    dispFunc.InitDisp = cursesDispInit;
    dispFunc.CloseDisp = cursesDispClose;
    dispFunc.DispHelp = cursesDispHelp;
    dispFunc.DispStatus = cursesDispStatus;
    dispFunc.DispBoard = cursesDispBoard;
    dispFunc.GetCmd = cursesGetCmd;

    //Try to initialize the display, exit on failure
    if(dispFunc.InitDisp(board) != EXIT_SUCCESS) {
        delBoard(board);
        free(buf);
        fprintf(stderr, "Failed to initialize the display, exit failure\n");
        return EXIT_FAILURE;
    }
    
    //========================================<Main Code>=========================================//
    //=======================================<Pre-Game>=======================================//
    // Display the help screen before the game begins
    dispFunc.DispHelp(kHelpChar, kNoteChar, kFlipChar, kQuitChar);
    
    // Display the board and status the first time around before grabbing any commands 
    dispFunc.DispStatus(score, requiredTiles, "Welcome to boltsphere flip!");
    dispFunc.DispBoard(board);
    
    //====================================<Main Game Loop>====================================//
    while(score > 0 && requiredTiles > 0) { //Repeat until flipped a 0 or all required tiles
        dispFunc.GetCmd(buf, kBufSize);
        switch(buf[0]){
            case kHelpChar:
                dispFunc.DispStatus(score, requiredTiles, "");
                dispFunc.DispHelp(kHelpChar, kNoteChar, kFlipChar, kQuitChar);

                dispFunc.DispStatus(score, requiredTiles, "Printed Help");
                break;
            case kQuitChar:
                score = 0;
                break;
            case kNoteChar:
            case kFlipChar: ; //semicolon here because screw C
                char colChar = buf[1];
                char rowChar = buf[2];
                
                size_t row = 0;
                size_t col = 0;
                if(colChar >= 'a' && colChar <= 'z' && colChar - 'a' < nCols) {
                    col = colChar - 'a';
                } else if (colChar >= 'A' && colChar <= 'Z' && colChar - 'A' < nCols) {
                    col = colChar - 'A';
                } else {
                    dispFunc.DispStatus(score, requiredTiles, "Illegal column");
                    dispFunc.DispBoard(board);
                    continue;
                }

                if(rowChar >= '1' && rowChar - '1' < nRows) {
                    row = rowChar - '1';
                } else {
                    dispFunc.DispStatus(score, requiredTiles, "Illegal row");
                    dispFunc.DispBoard(board);
                    continue;
                }

                if(buf[0] == kFlipChar) {
                    flipCard(board, row, col);
                    int cardScore = getScore(board, row, col);
                    if(cardScore == 0)
                        break;
                    else if(cardScore > 1)
                        requiredTiles -= 1;
                    score *= cardScore;
                    dispFunc.DispStatus(score, requiredTiles, buf);
                } else {
                    if(buf[3] < '0' || buf[3] > '3') {
                        dispFunc.DispStatus(score, requiredTiles, "You must specify a list of notes to toggle");
                    } else {
                        for(size_t i = 3; buf[i] >= '0' && buf[i] <= '3'; i++) { //Flip each listed flag it's listed
                            addNote(board, buf[i] - '0', row, col);
                        }
                        dispFunc.DispStatus(score, requiredTiles, buf);
                    }
                }

                break;
            default:
                dispFunc.DispStatus(score, requiredTiles, "Illegal command");
                break;
        }
        
        dispFunc.DispBoard(board);
    }

    //======================================<Post-Game>=======================================//
    revealBoard(board);
    dispFunc.DispStatus(score, requiredTiles, "GAME OVER");
    dispFunc.DispBoard(board);
    dispFunc.GetCmd(buf, kBufSize);

    //=========================================<Cleanup>==========================================//
    dispFunc.CloseDisp();
    delBoard(board);
    free(buf);
    return EXIT_SUCCESS;
}

