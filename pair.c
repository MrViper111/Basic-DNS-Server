#include "pair.h"
#include <string.h>
#include <stdlib.h>

int get_sep_index(char *line) {
    int length = strlen(line);
    int index;

    for (int i = 0; i < length; i++) {
        if (line[i] == ':') {
            index = i;
            break;
        }
    }

    return index;
}

pair_t* pair_init(char *line) {
    pair_t *pair = malloc(sizeof(pair_t));
    int sep_index = get_sep_index(line);

    if (sep_index == -1) {
        free(pair);
        return NULL;
    }
    
    pair->key = malloc(sep_index + 1);
    strncpy(pair->key, line, sep_index);
    pair->key[sep_index] = '\0';
    
    char *value_start = line + sep_index + 1;
    pair->value = malloc(strlen(value_start) + 1);
    strcpy(pair->value, value_start);
    
    return pair;
}

void pair_free(pair_t *pair) {
    free(pair->key);
    free(pair->value);
    free(pair);
}

