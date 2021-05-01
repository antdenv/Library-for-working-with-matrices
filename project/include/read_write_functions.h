#ifndef PROJECT_INCLUDE_READ_WRITE_FUNCTIONS_H_
#define PROJECT_INCLUDE_READ_WRITE_FUNCTIONS_H_

#include <stddef.h>  //  FILE
#include <stdio.h>  //  size_t
#include "test_functions.h"
#include "create_enums.h"

Task read_first_character(int symbol, Header* header);
Task read_first_word(FILE* file, Header header);
Task skip_line(FILE* file);

int search_for_boundaries(FILE* file, const char* boundary);

char* read_block(FILE* file);

size_t get_block_size(FILE* file);

#endif  // PROJECT_INCLUDE_READ_WRITE_FUNCTIONS_H_
