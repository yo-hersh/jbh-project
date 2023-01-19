#ifndef DB_H
#define DB_H
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct
{
    int day, mount, year
} Date;

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

typedef enum
{
    EQUAL,
    NOT_EQUAL,
    GREETER,
    SMALLER
} OPER_E;

void create_list(FILE *file);
void compare(Costumer *costumer, void *arr, int *arr_length, OPER_E oper);

// void compere(Costumer *costumer, void *arr, BSTNode *root, int *arr_length, OPER_E oper);

#endif