#include "printDisp.h"


#define kHoriBorder "+===+"
#define kHoriSpacer "  |  "

#define kNoteFormat "|%c|%c|"
#define kMiddleFormat "|-+-|"

#define kEmptyFormat "|   |"
#define kPointFormat "| %d |" 

void printBoard(board_t board) {
    if(board == NULL)
        return;
    
    //todo print out top row indicators
    
    for(size_t row = 0; row < getNRows(board); row++) {
        //todo print out left and right column indicators
        
        //Print a spacer from the line above
        for(size_t col = 0; col < getNCols(board); col++) {
            printf(" ");
            printf(kHoriSpacer);
        }
        printf("\n");
        
        //Print the upper border of the card
        for(size_t col = 0; col < getNCols(board); col++) {
            printf(" ");
            printf(kHoriBorder);
        }
        printf("\n");
        
        //If not flipped, print top row of notes, else print a blank line
        for(size_t col = 0; col < getNCols(board); col++) {
                printf(" ");
            if(isFlipped(board, row, col)) {
                printf(kEmptyFormat);
            } else {
                char notes = getNotes(board, row, col);
                printf(kNoteFormat, (notes & 0x1) ? '0' : ' ', 
                                    (notes & 0x2) ? '1' : ' ');
            }
        }
        printf("\n");
        
        //If flipped, print point value, else print centerline
        for(size_t col = 0; col < getNCols(board); col++) {
            printf("=");
            if(isFlipped(board, row, col)){
                printf(kPointFormat, getScore(board, row, col));
            } else {
                printf(kMiddleFormat);
            }
        }
        printf("=\n");
        
        //If not flipped, print bottom row of notes, else blank
        for(size_t col = 0; col < getNCols(board); col++) {
            printf(" ");
            if(isFlipped(board, row, col)) {
                    printf(kEmptyFormat);
            } else {
                char notes = getNotes(board, row, col);
                printf(kNoteFormat, (notes & 0x4) ? '2' : ' ', 
                                    (notes & 0x8) ? '3' : ' ');
            }
        }
        printf("\n");
        
        for(size_t col = 0; col < getNCols(board); col++) {
            printf(" ");
            printf(kHoriBorder);
        }
        printf("\n");
    }    
    
    
    for(size_t col = 0; col < getNCols(board); col++) {
        printf(" ");
        printf(kHoriSpacer);
    }
    printf("\n");
}

