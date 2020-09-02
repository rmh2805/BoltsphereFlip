#include <stdlib.h>
#include <stdio.h>

#include "board.h"

int main() {
    char score = 3;
    char status = 0x10 + (score<<5);
    
    printf("%d\n", status);
    printf("%d\n", status >> 5);
    printf("%s\n", (status&0x10)?"true":"false");
    
    return EXIT_SUCCESS;
}
