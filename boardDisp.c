#include "boardDisp.h"

//============================<Helper Declaration>============================//
size_t getBoardWidth(board_t board);
size_t getBoardHeight(board_t board);

size_t getCardRow(dispBuf_t buf, board_t board, int row);
size_t getCardCol(dispBuf_t buf, board_t board, int col);

void addCard(dispBuf_t* buf, board_t board, size_t row, size_t col, bool isSel);
void addHoriIndictors(dispBuf_t* buf, board_t board, size_t row, bool isSel);
void addVertIndictors(dispBuf_t* buf, board_t board, size_t col, bool isSel);
void addHoriSeparators(dispBuf_t* buf, board_t board, size_t row);
void addVertSeparators(dispBuf_t* buf, board_t board, size_t col);

//============================<Exposed Functions>=============================//
void addBoard(dispBuf_t* buf, board_t board) {
    if(buf == NULL || board == NULL) return;
    if(!bufFitsBoard(*buf, board)) return;

    size_t boardRows = getNRows(board);
    size_t boardCols = getNCols(board);

    // Add the indicators and separators
    for(size_t row = 0; row < boardRows; ++row) {
        addHoriIndictors(buf, board, row, false);
        addHoriSeparators(buf, board, row);
    }

    for(size_t col = 0; col < boardCols; ++col) {
        addVertIndictors(buf, board, col, false);
        addVertSeparators(buf, board, col);
    }

    // Add the cards
    for(size_t row = 0; row < boardRows; ++row) {
        for(size_t col = 0; col < boardCols; ++col) {
            addCard(buf, board, row, col, false);
        }
    }

    // Add the separators
}

void addBoardSel(dispBuf_t* buf, board_t board, size_t row, size_t col) {
    if(buf == NULL || board == NULL) return;
    if(!bufFitsBoard(*buf, board)) return;

    size_t boardRows = getNRows(board);
    size_t boardCols = getNCols(board);

    if(row >= boardRows) {

    } else if (col >= boardCols) {
        addHoriIndictors(buf, board, row, true);
        for(col = 0; col < boardCols; ++col) {
            addCard(buf, board, row, col, true);
        }
    } else if (row < boardRows && col < boardCols) {
        addCard(buf, board, row, col, true);
    }

}

bool bufFitsBoard(dispBuf_t buf, board_t board) {
    if(board == NULL) return false;

    size_t minRows = 0, minCols = 0;
    boardMinBufSize(board, &minRows, &minCols);

    return buf.screenRows >= minRows && buf.screenCols >= minCols;
}

void boardMinBufSize(board_t board, size_t* minRows, size_t* minCols) {
    if(board == NULL) return;

    // Compute the actual required dimensions
    if(minRows != NULL) *minRows = getBoardHeight(board) + 2 * kCardVertBorder;
    if(minCols != NULL) *minCols = getBoardWidth(board)  + 2 * kCardHoriBorder;
}

//=============================<Helper Functions>=============================//

size_t getBoardWidth(board_t board) {
    if(board == NULL) return 0;

    size_t cardCols = getNCols(board) + 2;
    return cardCols * kDefCardWidth + (cardCols-1) * kCardHoriSep;
}

size_t getBoardHeight(board_t board) {
    if(board == NULL) return 0;

    size_t cardRows = getNRows(board) + 2;
    return cardRows * kDefCardHeight + (cardRows-1) * kCardVertSep;
}

size_t getCardRow(dispBuf_t buf, board_t board, int row) {
    if(buf.data == NULL || board == NULL) return 0;
    if(!bufFitsBoard(buf, board)) return 0;

    // Get the top row of the board-top indicators, and update the row count
    size_t baseRow = buf.screenRows/2 - getBoardWidth(board)/2;
    size_t cardRow = row + 1;

    return baseRow + cardRow * (kDefCardHeight + kCardVertSep);
}

size_t getCardCol(dispBuf_t buf, board_t board, int col) {
    if(buf.data == NULL || board == NULL) return 0;
    if(!bufFitsBoard(buf, board)) return 0;

    // Get the top row of the board-top indicators, and update the row count
    size_t baseCol = buf.screenCols/2 - getBoardHeight(board)/2;
    size_t cardCol = col + 1;

    return baseCol + cardCol * (kDefCardWidth + kCardHoriSep);
}

void addCard(dispBuf_t* buf, board_t board, size_t row, size_t col, bool isSel) {
    if(buf == NULL || board == NULL) return;

    int startRow = getCardRow(*buf, board, row);
    int startCol = getCardCol(*buf, board, col);

    short palette = kDefPalette;
    int score = 0;
    bool flipped = isFlipped(board, row, col);
    if(!flipped) {
        palette = isSel ? kSelUnflippedPalette : kUnflippedPalette;
    } else if((score = getScore(board, row, col)) == 0) {
        palette = isSel ? kSelBadPalette : kBadPalette;
    } else {
        palette = isSel ? kSelSafePalette : kSafePalette;
    }

    // Draw the card base
    fillArea(buf, startRow, startCol, kDefCardWidth, kDefCardHeight, ' ', palette);

    // Draw the card data
    if(flipped) {
        char notes = getNotes(board, row, col);
        bool note0 = (notes & 0x01) ? true : false;
        bool note1 = (notes & 0x02) ? true : false;
        bool note2 = (notes & 0x04) ? true : false;
        bool note3 = (notes & 0x08) ? true : false;

        addChar(buf, startRow + 1*kDefCardHeight/4, startCol + 1*kDefCardWidth/4, 
                    note0 ? '0' : ' ', palette);
        addChar(buf, startRow + 1*kDefCardHeight/4, startCol + 3*kDefCardWidth/4, 
                    note1 ? '1' : ' ', palette);
        addChar(buf, startRow + 3*kDefCardHeight/4, startCol + 1*kDefCardWidth/4, 
                    note2 ? '2' : ' ', palette);
        addChar(buf, startRow + 3*kDefCardHeight/4, startCol + 3*kDefCardWidth/4, 
                    note3 ? '3' : ' ', palette);
    } else {
        char ch = '0' + score;
        addChar(buf, startRow + kDefCardHeight/2, startCol + kDefCardWidth/2, ch, palette);
    }
}

void addHoriIndictors(dispBuf_t* buf, board_t board, size_t row, bool isSel) {
    if(buf == NULL || board == NULL) return;

    short palette = isSel ? kSelIndicPalette : kIndicPalette;
    char outBuf[3];

    size_t boardCols = getNCols(board);
    size_t topRow = getCardRow(*buf, board, row);
    size_t leftCol = getCardCol(*buf, board, -1);
    size_t rightCol = getCardCol(*buf, board, boardCols);

    // Draw the indicator base
    fillArea(buf, topRow, leftCol, kDefCardWidth, kDefCardHeight, ' ', palette);
    fillArea(buf, topRow, rightCol, kDefCardWidth, kDefCardHeight, ' ', palette);

    // Draw the row number in the left-hand indicator
    addChar(buf, topRow + kDefCardHeight/2, leftCol + kDefCardWidth/2, '1' + row, palette);

    // Draw the total score and number of bombs in the right-hand indicator
    unsigned nBombs = 0;
    unsigned totalScore = 0;

    for(size_t col = 0; col < boardCols; ++col) {
        int score = getScore(board, row, col);
        if(score == 0) ++nBombs;
        totalScore += score;
    }

    sprintf(outBuf, "%u", (nBombs > 99) ? 99 : nBombs);
    addStr(buf, topRow + 1*kDefCardHeight/3, rightCol, "0:", palette);
    addStr(buf, topRow + 1*kDefCardHeight/3, rightCol + 3, outBuf, palette);
    sprintf(outBuf, "%u", (totalScore > 99) ? 99 : totalScore);
    addStr(buf, topRow + 2*kDefCardHeight/3, rightCol, outBuf, palette);
}

void addVertIndictors(dispBuf_t* buf, board_t board, size_t col, bool isSel) {
    if(buf == NULL || board == NULL) return;

    short palette = isSel ? kSelIndicPalette : kIndicPalette;
    char outBuf[3];

    size_t boardRows = getNRows(board);
    size_t leftCol = getCardCol(*buf, board, col);
    size_t topRow = getCardRow(*buf, board, -1);
    size_t bottomRow = getCardRow(*buf, board, boardRows);

    // Draw the indicator base
    fillArea(buf, topRow, leftCol, kDefCardWidth, kDefCardHeight, ' ', palette);
    fillArea(buf, bottomRow, leftCol, kDefCardWidth, kDefCardHeight, ' ', palette);

    // Draw the row number in the top indicator
    addChar(buf, topRow + kDefCardHeight/2, leftCol + kDefCardWidth/2, 'A' + col, palette);

    // Draw the total score and number of bombs in the right-hand indicator
    unsigned nBombs = 0;
    unsigned totalScore = 0;

    for(size_t row = 0; row < boardRows; ++row) {
        int score = getScore(board, row, col);
        if(score == 0) ++nBombs;
        totalScore += score;
    }

    sprintf(outBuf, "%u", (nBombs > 99) ? 99 : nBombs);
    addStr(buf, bottomRow + 1*kDefCardHeight/3, leftCol, "0:", palette);
    addStr(buf, bottomRow + 1*kDefCardHeight/3, leftCol + 3, outBuf, palette);
    sprintf(outBuf, "%u", (totalScore > 99) ? 99 : totalScore);
    addStr(buf, bottomRow + 2*kDefCardHeight/3, leftCol, outBuf, palette);
}

void addHoriSeparators(dispBuf_t* buf, board_t board, size_t row) {
    if(buf == NULL || board == NULL) return;

    size_t separators = getNCols(board) + 1;
    size_t screenRow = getCardRow(*buf, board, row) + kDefCardHeight/2;
    size_t screenCol = getCardCol(*buf, board, -1) + kDefCardWidth;

    for(size_t i = 0; i < separators; ++i) {
        for(int j = 0; j < kCardHoriSep; ++j) {
            addChar(buf, screenRow, screenCol+j, '-', kDefPalette);
        }
        screenCol += kDefCardWidth;
    }
}

void addVertSeparators(dispBuf_t* buf, board_t board, size_t col) {
    if(buf == NULL || board == NULL) return;

    size_t separators = getNRows(board) + 1;
    size_t screenRow = getCardRow(*buf, board, -1) + kDefCardHeight;
    size_t screenCol = getCardCol(*buf, board, col) + kDefCardWidth/2;

    for(size_t i = 0; i < separators; ++i) {
        for(int j = 0; j < kCardVertSep; ++j) {
            addChar(buf, screenRow+j, screenCol, '-', kDefPalette);
        }
        screenRow += kDefCardHeight;
    }
}
