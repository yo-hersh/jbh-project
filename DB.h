#ifndef DB_H
#define DB_H
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct
{
    char first_name[20];
    char last_name[20];
    unsigned int id;
    unsigned int phone;
    int dept;
    char date[11];
} Dept;

void create_list(FILE *file);
// int add_dept();
// void get_dept();

#endif