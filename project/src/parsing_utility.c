#include "create_enums.h"
#include "parsing.h"
#include "read_write_functions.h"
#include "boundary.h"

#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define STRING_COUNT 4
#define OUTPUT_COUNT 3

int parse_eml(const char* filepath) {
    FILE* file = fopen(filepath, "r");
    if (!file) {
        perror("ERROR");
        return 1;
    }

    Task task = READ_FIRST_CHARACTER;
    Header header = MISMATCH;
    char** out = (char**) calloc(STRING_COUNT, sizeof(char*));
    if (!out) {
        task = FORCED_END;
    }

    char* boundary_p = 0;
    int parts = 0;
    int declare[STRING_COUNT] = {0, 0, 0, 0};
    int symbol = 0;
    while (task) {
        switch (task) {
            case READ_FIRST_CHARACTER:
                symbol = fgetc(file);
                task = read_first_character(symbol, &header);
                break;
            case READ_FIRST_WORD:
                task = read_first_word(file, header);
                break;
            case SKIP_LINE:
                task = skip_line(file);
                break;
            case READ_BLOCK:
                if (declare[header]) {
                    task = SKIP_LINE;
                    break;
                }

                out[header] = read_block(file);
                if (!out[header]) {
                    task = FORCED_END;
                    break;
                }

                declare[header] = 1;
                if (header == CONTENT_TYPE) {
                    boundary_p = boundary(out[CONTENT_TYPE]);
                }
                break;
            case SEARCH_FOR_BOUNDARIES:
                if (!boundary_p) {
                    parts = 1;
                    task = END;
                    break;
                }

                parts = search_for_boundaries(file, boundary_p);
                task = END;
                break;
            case FORCED_END:
                if (file) {
                    fclose(file);
                }

                if (!out) {
                    return 1;
                }

                for (int i = 0; i < STRING_COUNT; ++i) {
                    if (out[i]) {
                        free(out[i]);
                    }
                }

                free(out);
                return 1;
            case END:
                break;
        }
    }

    fclose(file);

    for (int i = 0; i < OUTPUT_COUNT; ++i) {
        printf("%s|", out[i] ? out[i] : "");
    }

    printf("%d", parts);

    for (int i = 0; i < STRING_COUNT; ++i) {
        if (out[i]) {
            free(out[i]);
        }
    }

    if (boundary_p) {
        free(boundary_p);
    }

    free(out);
    return 0;
}
