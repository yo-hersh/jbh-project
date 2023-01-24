#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "str_handling.h"

void remove_white_spaces(char *str);
void str_to_lower(char *str);
int valid_date(char *str);
int valid_dept(char *str);
int valid_phone(char *str);
int valid_id(char *str);
int valid_name(char *str);
int is_not_only_digit(char *str);
int is_not_only_char(char *str);

void remove_white_spaces(char *str)
{
    int i = 0, j = 0;
    // char new_str[len] = {0};
    char *new_str = calloc(strlen(str)+1, sizeof(char));

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
    // free(&str);
    // return new_str;

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
    while (str)
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
    int i = 0;
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

    if (strlen(str) != 9 || !is_not_only_digit(str) || !(atoi(str) > 0))
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

    if (strlen(str) != 10 || !is_not_only_digit(str) || str[1] == '0' || str[0] != '0')
    {
        return 0;
    }

    return 1;
}

int valid_dept(char *str)
{
    if (!str)
    {
        return 0;
    }

    if (!is_not_only_digit(str) || atoi(str) == 0)
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
    char *temp_str = str;

    int day, month, year;
    char *value = strtok(temp_str, "/");
    int column = 1;
    while (value)
    {
        if (!is_not_only_digit(value))
        {
            return 0;
        }

        switch (column)
        {
        case 1:
            day = atoi(value);
            if (day <= 0 || day > 31)
            {
                return 0;
            }
            break;
        case 2:
            month = atoi(value);
            if (month <= 0 || month > 12)
            {
                return 0;
            }
            break;
        case 3:
            year = atoi(value);
            if (year <= 1970 || year > 2100)
            {
                return 0;
            }
            break;
        default:
            return 0;
            break;
        }
        value = strtok(NULL, "/");
        column++;
    }
    return 1;
}

void stringify_costumer(Costumer *costumer, char *buf, unsigned int len, unsigned int curr)
{
    snprintf(buf, len, "%s, %s, %09d, 0%d, %d, %d/%d/%d\n", costumer->first_name, costumer->last_name,
             costumer->id, costumer->phone, costumer->dept, costumer->date.year, costumer->date.month, costumer->date.day);
}

void print_costumer(Costumer *costumer)
{
    printf("%s, %s, %09d, 0%d, %d, %d/%d/%d\n", costumer->first_name, costumer->last_name, costumer->id, costumer->phone,
           costumer->dept, costumer->date.year, costumer->date.month, costumer->date.day);
}