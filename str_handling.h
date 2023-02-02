#ifndef STR_HANDLING_H
#define STR_HANDLING_H

#include "DB.h"

void remove_white_spaces(char *str);
void str_to_lower(char *str);
int valid_date(char *str);
int valid_dept(char *str);
int valid_phone(char *str);
int valid_id(char *str);
int valid_name(char *str);
int is_not_only_digit(char *str);
int is_not_only_char(char *str);
void stringify_costumer(Costumer *costumer, char *str, unsigned int len);
void print_costumer(Costumer *costumer, PRINT_HANDLING print, int print_to);

#endif