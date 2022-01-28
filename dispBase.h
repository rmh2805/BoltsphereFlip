#ifndef _DISP_INTERFACE_H_
#define _DISP_INTERFACE_H_

#include <stdlib.h>
#include <stdbool.h>

//============================<Const Definitions>=============================//
// Palette Definitions
#define kBlackPalette 1
#define kWhitePalette 2
#define kRedPalette 3
#define kGreenPalette 4
#define kBluePalette 5
#define kYellowPalette 6
#define kMagentaPalette 7
#define kCyanPalette 8

#define kDefPalette kBlackPalette
#define kNoPalette 0

//=============================<Type Definitions>=============================//
//=============================<Display Buffer>=============================//
/**
 * A simple struct to hold both display chars and their palettes in a single 
 * type
 */
typedef struct printPair_s {
    char ch;
    short palette;
} printPair_t;

/**
 * A common screen buffer
 */
typedef struct dispBuf_s {
    size_t screenRows;
    size_t screenCols;

    printPair_t** data;
} dispBuf_t;

//==============================<Display Core>==============================//
/**
 * A common set of display functions
 */
typedef struct disp_s {
    //========================<Display Open/Close>========================//
    /**
     * @brief Initialize the display (and allocate its internal data)
     * 
     * Usage: disp.init(&disp.data);
     * 
     * @param data A return pointer to initialize a display data store
     * 
     * @return 0 on success, <0 on failure
     */
    int (* init)(void** data);

    /**
     * @brief Close the display (and free its internal data)
     * 
     * Usage: disp.close(disp.data);
     * 
     * @param data The display's data store to free
     * 
     * @return 0 on success, <0 on failure
     */
    int (* close)(void* data);

    //==============================<Output>==============================//
    /**
     * @brief Simply prints text to the screen at the specified coordinates 
     * (no buffering, direct print)
     * 
     * Usage: disp.printText(disp.data, str, palette, row, col);
     * 
     * @param data The display's internal data store
     * @param str The string to print to screen
     * @param palette The palette to print the string in (if supported)
     * @param row The row to begin printing from (if supported)
     * @param col The column to begin printing from (if supported)
     */
    void (* printText)(void * data, const char * str, short palette, size_t row, size_t col);

    /**
     * @brief Prints the passed buffer out to the screen
     * 
     * Usage: disp.printBuf(disp.data, buf);
     * 
     * @param data The display's internal data store
     * @param buf The displayData buffer to print to screen
     * 
     * @return 0 on success. <0 on failure
     */
    int (* printBuf)(void * data, dispBuf_t buf);

    /**
     * @brief Clears the current screen
     * 
     * Usage: disp.clrScr(disp.data);
     * 
     * @param data The display's internal data store
     */
    void (* clearScr)(void* data);

    //==============================<Input>===============================//
    /**
     * @brief Gets the next input from the display
     * 
     * Usage: disp.getCh(disp.data);
     * 
     * @param data The display's data store
     * 
     * @return The read data
     */
    int (* getCh)(void* data);

    /**
     * @brief Reads the next string to end of line or buffer, whichever comes first
     * 
     * Usage: disp.getCh(disp.data, buf, nBuf);
     * 
     * @param data The display's data store
     * @param buf The buffer to read in to
     * @param nBuf The size of the buffer
     * 
     * @return The read data
     */
    void (* getStr)(void* data, char* buf, size_t nBuf);

    //=============================<Getters>==============================//
    /**
     * @brief Used to get the current screen size
     * 
     * Usage: disp.getStrSize(disp.data, &rows, &cols);
     * 
     * @param data The display's data store
     * @param rows A return pointer for the display's row count
     * @param cols A return pointer for the display's column count
     */
    void (* getScrSize)(void* data, size_t* rows, size_t* cols);

    //========================<Misc Display Info>=========================//
    bool monoDisp;  /** If initialized true, display does not support color */

    void* data;     /** A data store for this display */
} disp_t;


//===========================<Function Definitions>===========================//
//=============================<Type Builders>==============================//
/**
 * @brief Creates a display struct with all NULL function/data pointers
 * 
 * @return A display struct with all NULL function/data pointers
 */
disp_t mkNullDisp();

/**
 * @brief Creates a display buffer data struct
 * 
 * @param nRows The number of rows for the buffer
 * @param nCols The number of columns for the buffer
 * 
 * @return A display buffer with data space allocated (on failure, data will be
 *         NULL and dimensions will be zero)
 */
dispBuf_t mkDispBuf(size_t nRows, size_t nCols);

/**
 * @brief Frees all allocated data for the given display buf
 * 
 * @param buf The display buffer to free
 */
void rmDispBuf(dispBuf_t buf);

//=============================<Buffer Control>=============================//
/**
 * @brief Adds a character with the specified palette to the buffer
 * 
 * @param buf The display buffer to modify
 * @param row The row to add the character to
 * @param col The column to add the character to
 * @param ch The character to add
 * @param palette The palette to display the character in
 */
void addChar(dispBuf_t* buf, size_t row, size_t col, char ch, short palette);

/**
 * @brief Adds a string with the specified palette to the buffer
 * 
 * @param buf The display buffer to modify
 * @param row The row to start the string in
 * @param col The column to start the string in
 * @param str The string to add
 * @param palette The palette to display the string in
 */
void addStr(dispBuf_t* buf, size_t row, size_t col, const char * str, short palette);

/**
 * @brief Clears the provided buffer
 * 
 * @param buf The display buffer to clear
 */
void clearBuf(dispBuf_t* buf);

/**
 * @brief Fills a given area of the buffer with the specified character and palette
 * 
 * @param buf The buffer to modify
 * @param row The top row of the region to fill
 * @param col The left column of the region to fill
 * @param width The width of the region to fill
 * @param height The height of the region to fill
 * @param ch The character to fill the region with
 * @param palette The palette to fill the region with
 */
void fillArea(dispBuf_t* buf, size_t row, size_t col, size_t width, 
                size_t height, char ch, short palette);

#endif