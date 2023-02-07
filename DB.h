#ifndef DB_H
#define DB_H
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct
{
    int day, month, year;
} Date;

typedef struct
{
    char *first_name;
    char *second_name;
    unsigned int id;
    unsigned int phone;
    Date date;
    int debt;
} Costumer;
typedef void (*PRINT_HANDLING)(int, char *);

void create_list(FILE *file,PRINT_HANDLING print, int print_to);
void compare_str(char *str, char *oper, unsigned int index, PRINT_HANDLING print, int print_to);
int create_costumer(char *str, unsigned int line, PRINT_HANDLING print, int print_to);
void print_all(PRINT_HANDLING print, int print_to);
void free_all();

#endif