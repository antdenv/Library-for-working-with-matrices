#include "test_functions.h"
#include <stdio.h>

int is_endline(int symbol) {
    return symbol == '\n' || symbol == '\r';
}

int is_endline_duplet(int first_symbol, int second_symbol) {
    return (first_symbol == '\n' && second_symbol == '\r') || (first_symbol == '\r' && second_symbol == '\n');
}

int is_spacer(int symbol) {
    return symbol == ' ' || symbol == '\t';
}

int is_dash(int symbol) {
    return symbol == '-';
}

int is_eof(int symbol) {
    return symbol == EOF;
}


Header matches(int symbol) {
    if (symbol == SENDER_[0]) {
        return SENDER;
    } else if (symbol == RECEIVER_[0]) {
        return RECEIVER;
    } else if (symbol == DATE_[0]) {
        return DATE;
    } else if (symbol == CONTENT_TYPE_[0]) {
        return CONTENT_TYPE;
    } else {
        return MISMATCH;
    }
}
