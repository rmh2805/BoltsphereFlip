#include "dispBase.h"


//==============================<Type Builders>===============================//
disp_t mkNullDisp() {
    disp_t disp;

    // Create and NULL out the display
    for(size_t i = 0; i < sizeof(disp); ++i) {
        ((char *)(&disp))[i] = 0;
    }

    return disp;
}

dispBuf_t mkDispBuf(size_t nRows, size_t nCols) {
    dispBuf_t buf = {0, 0, NULL}; 
    if(nRows == 0 || nCols == 0) goto mkDispBuf_fail;

    // Create and NULL out the buf
    for(size_t i = 0; i < sizeof(buf); ++i) {
        ((char *)(&buf))[i] = 0;
    }

    // Set the dimensions
    buf.screenRows = nRows;
    buf.screenCols = nCols;

    // Allocate the data buffer
    if((buf.data = calloc(buf.screenRows, sizeof(printPair_t*))) == NULL) {
        goto mkDispBuf_fail;
    }

    for(size_t row = 0; row < buf.screenRows; ++row) {
        if((buf.data[row] = calloc(buf.screenCols, sizeof(printPair_t))) == NULL) {
            goto mkDispBuf_fail;
        }
    }

    clearBuf(&buf);
    return buf;

mkDispBuf_fail:
    rmDispBuf(buf);
    return (dispBuf_t){0, 0, NULL}; 
}

void rmDispBuf(dispBuf_t buf) {
    if(buf.data == NULL) return;

    for(size_t row = 0; row < buf.screenRows; ++row) {
        if(buf.data[row] != NULL) free(buf.data[row]);
    }
    free(buf.data);
}

//=============================<Buffer Control>=============================//
void addChar(dispBuf_t* buf, size_t row, size_t col, char ch, short palette) {
    if(buf == NULL || row >= buf->screenRows || col >= buf->screenCols || buf->data == NULL) return;

    if(!charPrintable(ch)) return;

    buf->data[row][col].ch = ch;
    buf->data[row][col].palette = palette;
}


void addStr(dispBuf_t* buf, size_t row, size_t col, const char * str, short palette) {
    if(buf == NULL || row >= buf->screenRows || col >= buf->screenCols || 
            buf->data == NULL || str == NULL) return;

    for(size_t dCol = 0; str[dCol] != '\0' && col + dCol < buf->screenCols; ++dCol) {
        addChar(buf, row, col+dCol, str[dCol], palette);
    }
}

void clearBuf(dispBuf_t* buf) {
    if(buf == NULL) return;
    fillArea(buf, 0, 0, buf->screenCols, buf->screenRows, ' ', kNoPalette);
}

void fillArea(dispBuf_t* buf, size_t row, size_t col, size_t width, 
                size_t height, char ch, short palette) {
    if(buf == NULL || buf->data == NULL) return;
    if(!charPrintable(ch)) return;

    for(size_t dRow = 0; row + dRow < buf->screenRows && dRow < height; ++dRow) {
        for(size_t dCol = 0; col + dCol < buf->screenCols && dCol < width; ++dCol) {
            buf->data[row+dRow][col+dCol].ch = ch;
            buf->data[row+dRow][col+dCol].palette = palette;
        }
    }
}

bool charPrintable(char ch) {
    return ch >= 0x20 && ch <= 0x7E;
}