#ifndef STR_HANDLING_H
#define STR_HANDLING_H

#include "DB.h"

#define BUF_LEN 1024
#define MSG_LEN 200

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

#endif