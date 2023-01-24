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
// void compare(Costumer *costumer, void *arr, int *arr_length, OPER_E oper);
typedef void*(*DO_FUNC)(Costumer *, void *);
// void compere(Costumer *costumer,  BSTNode *root, OPER_E oper, DO_FUNC do_func);
typedef void *(*DO_SOMETHING)(Costumer *);
// void compere(Costumer *costumer, void *arr, BSTNode *root, int *arr_length, OPER_E oper);
char *compare(Costumer *costumer, char *oper);
int add_date(char *str, Costumer *costumer);
int create_costumer(char *str, int line, char *error_msg);
void print();

// void tree_in_order(BSTNode *root, void(*do_something)(Costumer *costumer))

#endif