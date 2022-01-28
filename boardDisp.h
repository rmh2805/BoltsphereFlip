#ifndef _BOARD_DISP_H_
#define _BOARD_DISP_H_

#include <stdlib.h>

#include "board.h"
#include "dispBase.h"

// Define card palettes
#define kUnflippedPalette kGreenPalette
#define kSafePalette kBluePalette
#define kBadPalette kRedPalette

#define kSelUnflippedPalette kYellowPalette
#define kSelSafePalette kMagentaPalette
#define kSelBadPalette kCyanPalette

#define kIndicPalette kWhitePalette
#define kSelIndicPalette kBlackPalette

// Screenspace definitions
#define kDefCardWidth 7     /** The default width of a card (in characters)*/
#define kDefCardHeight 5    /** The default height of a card (in characters) */

#define kCardHoriSep 1      /** The horizontal separation b/n cards */
#define kCardVertSep 1      /** The vertical separation b/n cards */
#define kCardHoriBorder 1   /** The number of reserved columns to each side of the board */
#define kCardVertBorder 3   /** The number of reserved rows aboce and below the board */

/**
 * @brief Add a board to the buffer
 * 
 * @param buf The buffer to modify
 * @param board The board to add to the buffer
 */
void addBoard(dispBuf_t* buf, board_t board);

/**
 * @brief Add a board to the buffer with a card selected
 * 
 * @param buf The buffer to modify
 * @param board The board to add to the buffer
 * @param row The row of the card to select (> board height selects an entire column)
 * @param col The column of the card to select (> board heigh selects an entire row)
 */
void addBoardSel(dispBuf_t* buf, board_t board, size_t row, size_t col);

/**
 * @brief A simple check to determine if the buffer fits the board
 * 
 * @param buf The buffer to check for fit
 * @param board The board to check for fit
 * @return true The board fits in the buffer
 * @return false The board does not fit in the buffer
 */
bool bufFitsBoard(dispBuf_t buf, board_t board);

/**
 * @brief Computes the minimum rows and columns a buffer needs to fit the board
 * 
 * @param board The board to check
 * @param minRows A return pointer for the minimum number of rows needed to fit
 * @param minCols A return pointer for the minimum number of cols needed to fit
 */
void boardMinBufSize(board_t board, size_t* minRows, size_t* minCols);

#endif