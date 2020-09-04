#include "printDisp.h"


#define kHoriBorder "+===+"
#define kHoriSpacer "  |  "

#define kNoteFormat "|%c|%c|"
#define kMiddleFormat "|-+-|"

#define kEmptyFormat "|   |"
#define kPointFormat "| %c |" 

#define kBottomPointFormat "|%2d |"

#define kLBorder "==+"
#define kLIndicator " %c|"
#define kLBlank "  |"
#define kIndent "   "

#define kRBorder "+=="
#define kRIndicator "|%2d"
#define kRBlank "|  "

int printDispInit() {
    return EXIT_SUCCESS;
}

void printDispClose() {
    
} 

void printDispRow(board_t board, size_t row) {
    int totScore = 0;
    int totBombs = 0;
    
    for(size_t col = 0; col < getNCols(board); col++) {
        int score = getScore(board, row, col);
        totScore += score;
        totBombs += (score == 0) ? 1 : 0;
    }

    printf(kIndent);
    //Print a spacer from the line above
    for(size_t col = 0; col < getNCols(board); col++) {
        printf(" ");
        printf(kHoriSpacer);
    }
    printf("\n");
    
    printf(kLBorder);
    //Print the upper border of the card
    for(size_t col = 0; col < getNCols(board); col++) {
        printf(" ");
        printf(kHoriBorder);
    }
    printf(" ");
    printf(kRBorder);
    printf("\n");
    
    printf(kLBlank);
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
    printf(" ");
    printf(kRIndicator, totScore);
    printf("\n");
    
    printf(kLIndicator, (char)('1' + row));
    //If flipped, print point value, else print centerline
    for(size_t col = 0; col < getNCols(board); col++) {
        printf("=");
        if(isFlipped(board, row, col)){
            printf(kPointFormat, (char) ('0' + getScore(board, row, col)));
        } else {
            printf(kMiddleFormat);
        }
    }
    printf("=");
    printf(kRBlank);
    printf("\n");
    
    printf(kLBlank);
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
    printf(" ");
    printf(kRIndicator, totBombs);
    printf("\n");
    
    printf(kLBorder);
    for(size_t col = 0; col < getNCols(board); col++) {
        printf(" ");
        printf(kHoriBorder);
    }
    printf(" ");
    printf(kRBorder);
    printf("\n");
    
}

void printDispBoard(board_t board) {
    if(board == NULL)
        return;
    
    printf(kIndent);
    for(size_t col = 0; col < getNCols(board); col++) {
        printf(" ");
        printf(kPointFormat, (char)('A' + col));
    }
    printf("\n");
    
    printf(kIndent);
    for(size_t col = 0; col < getNCols(board); col++) {
        printf(" ");
        printf(kHoriBorder);
    }
    printf("\n");
    
    
    for(size_t row = 0; row < getNRows(board); row++) {
        printDispRow(board, row);
    }    
    
    printf(kIndent);
    for(size_t col = 0; col < getNCols(board); col++) {
        printf(" ");
        printf(kHoriSpacer);
    }
    printf("\n");
    
    printf(kIndent);
    for(size_t col = 0; col < getNCols(board); col++) {
        printf(" ");
        printf(kHoriBorder);
    }
    printf("\n");
    
    printf(kIndent);
    for(size_t col = 0; col < getNCols(board); col++) {
        int tot = 0;
        for(size_t row = 0; row < getNRows(board); row++) 
            tot += getScore(board, row, col);
        
        printf(" ");
        printf(kBottomPointFormat, tot%100);
    }
    printf("\n");
    
    printf(kIndent);
    for(size_t col = 0; col < getNCols(board); col++) {
        int tot = 0;
        for(size_t row = 0; row < getNRows(board); row++) 
            tot += (getScore(board, row, col) == 0) ? 1 : 0;
        
        printf(" ");
        printf(kBottomPointFormat, tot%100);
    }
    printf("\n");
    
    
}

void printDispHelp(char help, char note, char flip) {
    printf("%c: print this menu\n", help);
    printf("%c[col][row][value(s)]: Mark the specified card with the specified values (0-3)\n", note);
    printf("%c[col][row]: Flip the specified card\n", flip);
    fgetc(stdin);
}

void printDispStatus(size_t score, size_t nRemain, const char * msg) {
    printf("===================================================================\n");
    printf("Score: %lu\n", score);
    printf("Remaining Required Cards: %lu\n", nRemain);
    printf("%s\n", msg);
    printf("\n");
}

void printGetCmd(char * buf, size_t bufSize) {
    printf("\nEnter your command: ");
    fgets(buf, bufSize, stdin);
}
