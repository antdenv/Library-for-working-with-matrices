#include "parsing.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, const char **argv) {
    if (argc != 2) {
        return -1;
    }

    const char *path_to_eml = argv[1];

    if (parse_eml(path_to_eml)) {
        return 1;
    }

    return 0;
}
