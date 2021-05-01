#include "boundary.h"
#include <string.h>
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>

#define MULTIPART   "multipart"
#define MULTIPART_  "MULTIPART"
#define BOUNDARY    "boundary"
#define BOUNDARY_   "BOUNDARY"

char *boundary(char *str) {
    char *dublicate = str;
    size_t i = 0;
    size_t length = strlen(MULTIPART);
    while (i < length && *dublicate) {
        if (*dublicate == MULTIPART[i] || *dublicate == MULTIPART_[i]) {
            i++;
        } else {
            i = 0;
        }
        dublicate++;
    }

    if (i != length) {
        return NULL;
    }

    i = 0;

    char *pos = strstr(dublicate, BOUNDARY);
    char *pos_ = strstr(dublicate, BOUNDARY_);

    if (pos != NULL || pos_ != NULL) {
        if (pos > dublicate && isalnum(*(pos - 1))) {
            return NULL;
        }
        if (pos_ > dublicate && isalnum(*(pos_ - 1))) {
            return NULL;
        }
    } else {
        return NULL;
    }

    length = strlen(BOUNDARY);
    while (i < length && *dublicate) {
        if (*dublicate == BOUNDARY[i] || *dublicate == BOUNDARY_[i]) {
            i++;
        } else {
            i = 0;
        }
        dublicate++;
    }

    while (*dublicate != '=' && *dublicate) {
        dublicate++;
    }

    dublicate++;

    while (*dublicate == ' ' || *dublicate == '\t') {
        dublicate++;
    }

    if (!strlen(dublicate)) {
        return NULL;
    }

    if (*dublicate == '\"') {
        dublicate++;
    }

    for (i = 0; dublicate[i] != ' ' && dublicate[i] != '\"' && dublicate[i] != '\0'; ++i) {
        continue;
    }

    char *boundary = (char *) malloc((i + 1) * sizeof(char));
    snprintf(boundary, i + 1, "%s", dublicate);
    return boundary;
}
