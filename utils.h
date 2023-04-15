#ifndef UTILS_H
#define UTILS_H
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BUF_LEN 1024
#define MSG_LEN 200
#define ARR_LEN(_arr) (sizeof(_arr) / sizeof(_arr[0]))

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
} Customer;

typedef enum
{
    FIRST_NAME,
    SECOND_NAME,
    ID,
    PHONE,
    DATE,
    DEBT,
    SIZEOF_VALUES
} VALUES_E;

typedef enum
{
    SET,
    SELECT,
    SIZEOF_OPTIONS
} OPTIONS_E;

typedef enum
{
    DAY,
    MONTH,
    YEAR,
    SIZEOF_DATES
} DATE_E;

typedef enum
{
    MASSAGE,
    DISPLAY_OPTION,
    SELECT_HELP,
    SET_HELP
} MASSAGE_E;

// The implementation of this function is provided by the server or local file and is responsible for printing the result to a specific output.
typedef void (*PRINT_HANDLING)(int, const char *);
#endif