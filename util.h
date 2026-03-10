#ifndef UTIL_H
#define UTIL_H

#include <stdint.h>

int write_to(char *path, char *content);
uint32_t get_value(char *path, char *key);
int wipe(char *path);

#endif // UTIL_H
