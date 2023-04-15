#ifndef DB_H
#define DB_H
#include "utils.h"

void create_list(FILE *file);
void compare_str(char *str, char *oper, VALUES_E field, PRINT_HANDLING print, int print_to);
int create_customer(char *str, unsigned int line, PRINT_HANDLING print, int print_to);
void print_all(PRINT_HANDLING print, int print_to);
void free_all();

#endif