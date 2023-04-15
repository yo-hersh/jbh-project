#ifndef STR_HANDLING_H
#define STR_HANDLING_H
#include "utils.h"

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
void print_massage(MASSAGE_E type);

#endif