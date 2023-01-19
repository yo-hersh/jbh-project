#ifndef DB_H
#define DB_H
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct
{
    int day, mount, year
}Date;

typedef struct
{
    char *first_name;
    // char first_name[20];
    char *last_name;
    unsigned int id;
    unsigned int phone;
    int dept;
    Date date;
    // char *date;
} Costumer;

typedef struct 
{
    char *value;
    char *oper;
    char *find_value;
}Comp;


void create_list(FILE *file);
void *compere(Comp *comp);

#endif