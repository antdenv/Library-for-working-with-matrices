#include "read_write_functions.h"
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

Task read_first_character(int symbol, Header* header) {
    if (is_endline(symbol)) {
        return SEARCH_FOR_BOUNDARIES;
    }

    if (is_spacer(symbol)) {
        return SKIP_LINE;
    }

    *header = matches(symbol);
    if (*header == MISMATCH) {
        return SKIP_LINE;
    }

    return READ_FIRST_WORD;
}

Task read_first_word(FILE* file, Header header) {
    if (!file) {
        errno = 0;
        perror("");
        return FORCED_END;
    }

    char* key;
    switch (header) {
        case SENDER:
            key = SENDER_;
            break;
        case RECEIVER:
            key = RECEIVER_;
            break;
        case DATE:
            key = DATE_;
            break;
        case CONTENT_TYPE:
            key = CONTENT_TYPE_;
            break;
        default:
            return SKIP_LINE;
    }

    int mismatch = 0;
    for (size_t i = 1; i < strlen(key) && !mismatch; ++i) {
        int symbol = fgetc(file);
        if (symbol != key[i]) {
            mismatch = 1;
        }
    }

    if (mismatch) {
        return SKIP_LINE;
    }

    return READ_BLOCK;
}

Task skip_line(FILE* file) {
    if (!file) {
        return FORCED_END;
    }

    int symbol = fgetc(file);
    while (!is_endline(symbol) && !is_eof(symbol)) {
        symbol = fgetc(file);
    }

    if (is_eof(symbol)) {
        return END;
    }

    int pr_symbol = symbol;
    symbol = fgetc(file);
    if (is_endline_duplet(symbol, pr_symbol)) {
        return READ_FIRST_CHARACTER;
    }

    fseek(file, -1, SEEK_CUR);
    return READ_FIRST_CHARACTER;
}

char* read_block(FILE* file) {
    if (!file) {
        return NULL;
    }

    int symbol = fgetc(file);
    while (is_spacer(symbol)) {
        symbol = fgetc(file);
    }

    size_t size = get_block_size(file);

    char* block = (char*) malloc((size + 1) * sizeof(char));
    if (!block) {
        return NULL;
    }

    for (size_t i = 0; i < size; ++i) {
        if (is_endline(symbol)) {
            symbol = fgetc(file);

            while (is_endline(symbol)) {
                symbol = fgetc(file);
            }

            while (is_spacer(symbol)) {
                symbol = fgetc(file);
            }
            block[i] = ' ';
        } else {
            block[i] = (char) symbol;
            symbol = fgetc(file);
        }
    }

    fseek(file, -1, SEEK_CUR);
    block[size] = '\0';
    return block;
}

size_t get_block_size(FILE* file) {
    long init = ftell(file);
    size_t size = 0;
    int end = 0;
    int symbol = fgetc(file);

    while (!is_eof(symbol) && !end) {
        if (is_endline(symbol)) {
            int pr_symbol = symbol;
            symbol = fgetc(file);
            if (is_endline(symbol)) {
                if (!is_endline_duplet(symbol, pr_symbol)) {
                    end = 1;
                } else {
                    symbol = fgetc(file);
                }
            }

            if (!is_spacer(symbol)) {
                end = 1;
            } else {
                while (is_spacer(symbol)) {
                    symbol = fgetc(file);
                }
                size++;
            }
        }
        size++;
        symbol = fgetc(file);
    }

    if (!size) {
        return 0;
    }

    long finish = ftell(file);
    fseek(file, init - finish, SEEK_CUR);
    return size;
}

int search_for_boundaries(FILE* file, const char* boundary) {
    if (!file) {
        return -1;
    }

    int parts = 0;

    fseek(file, -1, SEEK_CUR);
    int symbol = fgetc(file);
    while (symbol != EOF) {
        if (!is_endline(symbol)) {
            symbol = fgetc(file);
            continue;
        }

        symbol = fgetc(file);

        if (!is_dash(symbol)) {
            continue;
        }

        symbol = fgetc(file);
        if (!is_dash(symbol)) {
            continue;
        }

        int mismatch = 0;
        for (size_t i = 0; i < strlen(boundary) && !mismatch; ++i) {
            symbol = fgetc(file);
            if (symbol != boundary[i]) {
                mismatch = 1;
            }
        }

        if (mismatch) {
            continue;
        }

        symbol = fgetc(file);
        if (is_endline(symbol)) {
            parts++;
        }

        if (!is_dash(symbol)) {
            continue;
        }

        symbol = fgetc(file);
        if (!is_dash(symbol)) {
            continue;
        }

        break;
    }

    return parts;
}
