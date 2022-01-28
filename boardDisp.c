#include "boardDisp.h"

//============================<Helper Declaration>============================//
size_t getBoardWidth(board_t board);
size_t getBoardHeight(board_t board);

size_t getCardRow(dispBuf_t buf, board_t board, int row);
size_t getCardCol(dispBuf_t buf, board_t board, int col);

//============================<Exposed Functions>=============================//
void addBoard(dispBuf_t* buf, board_t board) {
    if(buf == NULL || board == NULL) return;
}

void addBoardSel(dispBuf_t* buf, board_t board, size_t row, size_t col) {

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
