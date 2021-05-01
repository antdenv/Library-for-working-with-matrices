#ifndef PROJECT_INCLUDE_TEST_FUNCTIONS_H_
#define PROJECT_INCLUDE_TEST_FUNCTIONS_H_

#include "create_enums.h"

//  Use in files: test_utils.c , read_write_utils.c
#define SENDER_         "From:"
#define RECEIVER_       "To:"
#define DATE_           "Date:"
#define CONTENT_TYPE_   "Content-Type:"

Header matches(int symbol);

int is_endline(int symbol);
int is_endline_duplet(int first_symbol, int second_symbol);
int is_spacer(int symbol);
int is_dash(int symbol);
int is_eof(int symbol);

#endif  // PROJECT_INCLUDE_TEST_FUNCTIONS_H_
