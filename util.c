#include <stdio.h>
#include <arpa/inet.h>
#include <string.h>

#include "pair.h"

int write_to(char *path, char *content) {
    FILE *file = fopen(path, "a");

    if (file == NULL) {
        return -1;
    }

    if (fprintf(file, "%s\n", content) < 0) {
        fclose(file);
        return -2;
    }

    fclose(file);
    return 0;
}

uint32_t get_value(char *path, char *key) {
    FILE *file = fopen(path, "r");

    if (file == NULL) {
        return -1;
    }

    char line[512];
    while (fgets(line, sizeof(line), file) != NULL) {
        line[strcspn(line, "\n")] = '\0';

        pair_t *pair = pair_init(line);
        if (pair == NULL) {
            continue;
        }

        if (strcmp(pair->key, key) == 0) {
            uint32_t result = inet_addr(pair->value);

            pair_free(pair);
            fclose(file);

            return result;
        }

        pair_free(pair);
    }

    fclose(file);
    return 0;
}

int wipe(char *path) {
    FILE *file = fopen(path, "w");

    if (file == NULL) {
        return -1;
    }

    fclose(file);
    return 0;
}

