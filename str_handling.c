#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "str_handling.h"

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
void print_massage(MASSAGE_E type);

void remove_white_spaces(char *str)
{
    unsigned int i = 0, j = 0;
    if (!str)
    {
        return;
    }
    char *new_str = calloc(strlen(str) + 1, sizeof(char));
    if (!new_str)
    {
        perror("error creating new str");
        return;
    }

    for (i = 0; str[i]; i++)
    {
        if (str[i] == ' ')
        {
            if (j == 0 || str[i + 1] == ' ' || str[i + 1] == '\0')
            {
                continue;
            }
        }
        new_str[j++] = str[i];
    }
    strcpy(str, new_str);
    free(new_str);
}

int is_not_only_char(char *str)
{
    while ((*str) != '\0')
    {
        if (str[0] != 32 && (str[0] > 127 || str[0] < 97))
        {
            return 1;
        }
        str++;
    }
    return 0;
}

int is_not_only_digit(char *str)
{
    while (str[0])
    {
        if (str[0] < 48 || str[0] > 57)
        {
            return 1;
        }
        str++;
    }
    return 0;
}

void str_to_lower(char *str)
{
    unsigned int i = 0;
    while (str[i])
    {
        if (str[i] >= 65 && str[i] <= 90)
        {
            str[i] += 32;
        }
        i++;
    }
}

int valid_name(char *str)
{
    if (!str)
    {
        return 0;
    }

    if (strlen(str) <= 2 || is_not_only_char(str))
    {
        return 0;
    }

    return 1;
}

int valid_id(char *str)
{
    if (!str)
    {
        return 0;
    }

    if (strlen(str) != 9 || is_not_only_digit(str) || !(atoi(str) > 0))
    {
        return 0;
    }

    return 1;
}

int valid_phone(char *str)
{
    if (!str)
    {
        return 0;
    }

    if (strlen(str) != 10 || is_not_only_digit(str) || str[1] == '0' || str[0] != '0')
    {
        return 0;
    }

    return 1;
}

int valid_debt(char *str)
{
    if (!str)
    {
        return 0;
    }

    // for - by the str[0]
    if (str[0] == 45)
    {
        str++;
    }

    if (is_not_only_digit(str) || atoi(str) == 0)
    {
        return 0;
    }

    return 1;
}

int valid_date(char *str)
{
    if (!str)
    {
        return 0;
    }

    char *temp_str = calloc(strlen(str) + 1, sizeof(char));
    if (!temp_str)
    {
        perror("error creating str for date test");
        return 0;
    }
    char *ptr;

    strcpy(temp_str, str);

    unsigned int day, month, year;
    char *value = strtok_r(temp_str, "/", &ptr);
    int column = 0;

    for (int i = 0; i < SIZEOF_DATES; i++)
    {
        if (!value || is_not_only_digit(value))
        {
            goto exit;
        }

        switch (column)
        {
        case DAY:
            day = atoi(value);
            if (day <= 0 || day > 31)
            {
                goto exit;
            }
            break;
        case MONTH:
            month = atoi(value);
            if (month <= 0 || month > 12)
            {
                goto exit;
            }
            break;
        case YEAR:
            year = atoi(value);
            if (year <= 1970 || year > 2100)
            {
                goto exit;
            }
            break;
        }
        value = strtok_r(NULL, "/", &ptr);
        column++;
    }
    if (value)
    {
        goto exit;
    }
    free(temp_str);
    return 1;
exit:
    free(temp_str);
    return 0;
}

void stringify_customer(Customer *customer, char *str, unsigned int len)
{
    snprintf(str, len, "%s, %s, %09d, 0%d, %02d/%02d/%d, %d\n", customer->first_name, customer->second_name,
             customer->id, customer->phone, customer->date.day, customer->date.month, customer->date.year, customer->debt);
}

void print_customer(Customer *customer, PRINT_HANDLING print, int print_to)
{
    unsigned int len = strlen(customer->first_name) + strlen(customer->second_name) + 50;
    char *str = malloc(len * sizeof(char));
    if (!str)
    {
        perror("error creating stringy customer");
        return;
    }
    stringify_customer(customer, str, len);
    print(print_to, str);
    free(str);
}

void print_to_stdout(int socket_id, const char *str)
{
    printf("%s", str);
}

int buf_overflow(char *buf, PRINT_HANDLING print, int print_to)
{
    if (buf[strlen(buf) - 1] == '\n')
    {
        buf[strlen(buf) - 1] = '\0';
        return 0;
    }
    else
    {
        print(print_to, "buffer overflow\n");
        return 1;
    }
}

int add_f_name(Customer *customer, char *value)
{
    customer->first_name = calloc(strlen(value) + 1, sizeof(char));
    if (!customer->first_name)
    {
        perror("error creating first name");
        return 0;
    }
    strcpy(customer->first_name, value);
    return 1;
}
int add_s_name(Customer *customer, char *value)
{
    customer->second_name = calloc(strlen(value) + 1, sizeof(char));
    if (!customer->second_name)
    {
        perror("error creating second name");
        return 0;
    }
    strcpy(customer->second_name, value);
    return 1;
}
int add_id(Customer *customer, char *value)
{
    customer->id = atoi(value);
    return 1;
}
int add_phone(Customer *customer, char *value)
{
    customer->phone = atoi(value);
    return 1;
}
int add_debt(Customer *customer, char *value)
{
    customer->debt = atoi(value);
    return 1;
}
int add_date(Customer *customer, char *value)
{

    char *ptr;

    char *t_value = strtok_r(value, "/", &ptr);
    int column = 1;
    while (t_value)
    {
        switch (column)
        {
        case DAY:
            customer->date.day = atoi(t_value);
            break;
        case MONTH:
            customer->date.month = atoi(t_value);
            break;
        case YEAR:
            customer->date.year = atoi(t_value);
            break;
        }
        t_value = strtok_r(NULL, "/", &ptr);
        column++;
    }
    return 1;
}

void print_massage(MASSAGE_E type)
{
    char display_option[] = "--please select options: set <value> / select <value> / print\n--use <option> --help to see more\n--type quit to exit\n",
         select_help[] = "--select <value> <operation> <everything>.\n",
         set_help[] = "--set <value> = <everything>.\n",
         values_help[] = "--values: first name, last name, id, phone, date, debt.\n",
         massage[] = "--------------------STORE DATABASE---------------------\n--Enter a 5 messages, to send it enter send. for options enter halp\n";

    switch (type)
    {
    case MASSAGE:
        printf("%s", massage);
        break;
    case DISPLAY_OPTION:
        printf("%s", display_option);
        break;
    case SELECT_HELP:
        printf("%s%s", select_help, values_help);
        break;
    case SET_HELP:
        printf("%s%s", set_help, values_help);
        break;
    default:
        break;
    }
}