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
    char *last_name;
    unsigned int id;
    unsigned int phone;
    int dept;
    Date date;
} Costumer;

void create_list(FILE *file);
char *compare_str(char *str, char *oper, unsigned int index, char *error_msg);
int create_costumer(char *str, unsigned int line, char *error_msg);
void print();
void free_all();

#endif