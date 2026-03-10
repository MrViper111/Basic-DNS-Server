#ifndef PAIR_H
#define PAIR_H

typedef struct {
    char *key;
    char *value;
} pair_t;

int get_sep_index(char *line);
pair_t* pair_init(char *line);
void pair_free(pair_t *pair);

#endif // PAIR_H
