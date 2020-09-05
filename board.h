#ifndef  _BOARD_H_
#define  _BOARD_H_

#include <stdlib.h>
#include <stdbool.h>

typedef struct board_s * board_t;

//============================<Allocation>============================//
/**
 * Makes an empty board (scores 0) of default size
 */
board_t makeBoardDef();

/**
 * Makes an empty board (scores 0) with the specified size
 */
board_t makeBoard(size_t nCols, size_t nRows);

/**
 * Frees the board
 */
void delBoard(board_t board);

//==========================<Initialization>==========================//
/**
 * Initializes the scores on the board to random values (assumes sRand 
 * has already been set).
 */
void randInit(board_t board);

/**
 * Sets the score of the specified cell
 */
void setScore(board_t board, char score, size_t row, size_t col);

//==========================<Note Handling>===========================//
/**
 * Returns the bitfield of the notes in the particular cell. Any LSB 
 * bits 0-3 that have been set indicate the card is marked for those 
 * values.
 */
char getNotes(board_t board, size_t row, size_t col);

/**
 * Sets the note for score 'val' on the specified card
 */
void addNote(board_t board, char val, size_t row, size_t col);

//==========================<Flip Controls>===========================//
/**
 * Invert the flipped state of this card
 */
void flipCard(board_t board, size_t row, size_t col);

/**
 * Reveal every card on the board
 */
void revealBoard(board_t board);

/**
 * Returns true if this card is turned up
 */
bool isFlipped(board_t board, size_t row, size_t col);


//===========================<State Query>============================//
/**
 * Returns the score of the specified cell
 */
int getScore(board_t board, size_t row, size_t col);

/**
 * Returns the number of rows of the board
 */
size_t getNRows(board_t board);

/**
 * Returns the number of columns of the board
 */
size_t getNCols(board_t board);

#endif //_BOARD_H_
