#ifndef STR_HANDLING_H
#define STR_HANDLING_H

#include "DB.h"

#define BUF_LEN 1024
#define MSG_LEN 200

typedef enum{
    FIRST_NAME, SECOND_NAME, ID, PHONE, DATE, DEBT, SIZEOF_VALUES = 6
}VALUES_E;

typedef enum{
    SET, SELECT, SIZEOF_OPTIONS = 2
}OPTIONS_E;

// const char *error_msgs[] = {
//   "first name required to be letters only, at least 2\n",
//   "id required to be 9 digits only\n",
//   "phone required to be 10 digits only, start by 0\n",
//   "date required to be in dd/mm/yyyy format between 1970-2100\n",
//   "debt required to be digits only\n"
// };

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
void print_to_stdout(int socket_id, char *str, ...);
int add_f_name( Customer *customer, char *value);
int add_s_name( Customer *customer, char *value);
int add_id( Customer *customer, char *value);
int add_phone( Customer *customer, char *value);
int add_date(Customer *customer, char *value);
int add_debt( Customer *customer, char *value);
int too_many_values(char *str);


#endif