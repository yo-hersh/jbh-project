#ifndef DB_H
#define DB_H
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct
{
    char *first_name;
    // char first_name[20];
    char *last_name;
    unsigned int id;
    unsigned int phone;
    int dept;
    char *date;
} Dept;

void create_list(FILE *file);

#endif