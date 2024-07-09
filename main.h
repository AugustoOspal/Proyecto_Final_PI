#ifndef PROYECTO_FINAL_PI_MAIN_H
#define PROYECTO_FINAL_PI_MAIN_H

#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>
#include <string.h>

#define BUFFER 300
#define DELIM ";"
#define NUMBER_INPUT_FILES 2

// Error codes
#define ERROR_NUMBER_INPUT_FILES 1
#define ERROR_EMPTY_FILE 2
#define ERROR_INVALID_CITY_CODE 3
#define ERROR_ALLOCATING_MEMORY 4


// Error messages
#define ERROR_NUMBER_INPUT_FILES_M "Incorrect number of input files"
#define ERROR_EMPTY_FILE_M "There's at least one empty file"
#define ERROR_INVALID_CITY_CODE_M "Invalid city code"
#define ERROR_ALLOCATING_MEMORY_M "Not enough memory to allocate"

#endif //PROYECTO_FINAL_PI_MAIN_H
