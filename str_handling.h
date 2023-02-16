#ifndef STR_HANDLING_H
#define STR_HANDLING_H

#include "DB.h"

#define BUF_LEN 1024
#define MSG_LEN 200

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

#define display_option  "--please select options: set <value> / select <value> / print\n--use <option> --help to see more\n--type quit to exit\n"
#define select_help  "--select <value> <operation> <everything>.\n"
#define set_help  "--set <value> = <everything>.\n"
#define values_help  "--values: first name, last name, id, phone, date, debt.\n"
#define massage  "--------------------STORE DATABASE---------------------\n--Enter a 5 messages, to send it enter send. for options enter halp\n"

#define ARR_LEN(_arr) (sizeof(_arr) / sizeof(_arr[0]))

void remove_white_spaces(char *str);
void str_to_lower(char *str);
int valid_date(char *str);
int valid_debt(char *str);
int valid_phone(char *str);
int valid_id(char *str);
int valid_name(char *str);
int is_not_only_digit(char *str);
int is_not_only_char(char *str);
int buf_overflow(char *buf, PRINT_HANDLING print, int print_to);
void stringify_customer(Customer *customer, char *str, unsigned int len);
void print_customer(Customer *customer, PRINT_HANDLING print, int print_to);
void print_to_stdout(int socket_id, const char *str);
int add_f_name(Customer *customer, char *value);
int add_s_name(Customer *customer, char *value);
int add_id(Customer *customer, char *value);
int add_phone(Customer *customer, char *value);
int add_date(Customer *customer, char *value);
int add_debt(Customer *customer, char *value);

#endif