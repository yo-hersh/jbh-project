#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "str_handle.h"

char *remove_white_spaces(char *str, int len);
void str_to_lower(char *str);
int valid_date(char *str, Costumer *costumer);
int valid_dept(char *str);
int valid_phone(char *str);
int valid_id(char *str);
int valid_name(char *str);
int is_not_only_digit(char *str);
int is_not_only_char(char *str);
// void add_to_error_str(char *error_str, int line_num, char *value);
void print_err(char *str, int line);

Costumer *create_dept_from_str(char *str, int line)
{
    Costumer *new = calloc(1, sizeof(Costumer));
    // char *line_str;
    // if (line)
    // {
    //     strcat(line_str, "Line ");
    //     strcat(*line_str, *(char *)line);
    //     strcat(line_str, ": ");

    //     // line_str = "Line " + line + ": ";
    // }

    int is_error = 0;
    // char *error_arr[] = {0};

    str_to_lower(str);
    str = remove_white_spaces(str, strlen(str) + 1);

    char *value = strtok(str, ",");
    int column = 1;
    while (value)
    {
        value = remove_white_spaces(value, strlen(str) + 1);

        switch (column)
        {
        case 1:
            if (valid_name(value))
            {
                new->first_name = value;
            }
            else
            {
                print_err("first name not in the real format", line);
                // printf("%serror: first name not in the real format\n", line_str);
                // is_error = 1;
            }
            break;
        case 2:
            if (valid_name(value))
            {
                new->last_name = value;
            }
            else
            {
                // printf("%serror: last name not in the real format\n", line_str);
                is_error = 1;
            }
            break;
        case 3:
            if (valid_id(value))
            {
                new->id = atoi(value);
            }
            else
            {
                // printf("%serror: last name not in the real format\n", line_str);
                is_error = 1;
            }
            break;
        case 4:
            if (valid_phone(value))
            {
                new->phone = atoi(value);
            }
            else
            {
                // printf("%serror: last name not in the real format\n", line_str);
                is_error = 1;
            }
            break;
        case 5:
            if (valid_dept(value))
            {
                new->dept = atoi(value);
            }
            else
            {
                // printf("%serror: last name not in the real format\n", line_str);
                is_error = 1;
            }
            break;
        case 6:
            if (!valid_date(value, new))
            {
                // printf("%serror: last name not in the real format\n", line_str);
                is_error = 1;
            }
            break;
        default:
            break;
        }
        column++;
        value = strtok(NULL, ",");
    }
    if (is_error)
    {
        return NULL;
    }

    return new;
};

// int invalid_string(char *str, char *value)
// {
//     // before if(!*str) for a space only input
//     str = remove_white_spaces(str, strlen(str) + 1);
//     if (!*str)
//     {
//         return 1;
//     }
//     str_to_lower(str);
//     return is_not_only_char(str);
// }

// int valid_num(char *str)
// {
//     if (!str)
//     {
//         return 1;
//     }
//     str = remove_white_spaces(str, strlen(str) + 1);

//     return is_not_only_char(str);
// }

char *remove_white_spaces(char *str, int len)
{
    int i = 0, j = 0;
    char *new_str = calloc(len, sizeof(char));

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
    return new_str;
};

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
};

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
};

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
};

// void add_to_error_str(char *error_str, int line_num, char *value)
// {
//     error_str += line_num + "invalid " + value ", contain last one cher, char only";
// }

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
};

int valid_id(char *str)
{
    if (!str)
    {
        return 0;
    }
    printf("%d\n", strlen(str));
    // if (strlen(str) != 9 || !is_not_only_digit(str) || !(atoi(str) > 0))
    if (strlen(str) != 9)
    {
        return 0;
    }
    if (!is_not_only_digit(str))
    {
        return 0;
    }
    if (!(atoi(str) > 0))
    {
        return 0;
    }

    return 1;
};

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
};

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
};

int valid_date(char *str, Costumer *costumer)
{
    if (!str)
    {
        return 0;
    }

    int day, month, year;
    char *value = strtok(str, "/");
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
            costumer->date.day = day;
            break;
        case 2:
            month = atoi(value);
            if (month <= 0 || month > 12)
            {
                return 0;
            }
            costumer->date.month = month;
            break;
        case 3:
            year = atoi(value);
            if (year <= 1970 || year > 3000)
            {
                return 0;
            }
            costumer->date.year = year;
            break;
        default:
            break;
        }
        value = strtok(NULL, "/");
        column++;
    }
    return 1;
};

void print_err(char *str, int line)
{
    printf("error");
    if (line)
    {
        printf("line %d", line);
    }
    printf(": %s\n", str);
};

char *concat(const char *s1, const char *s2)
{
    int len1 = strlen(s1);
    int len2 = strlen(s2);
    char *result = malloc(len1 + len2 + 1); // +1 for the null-terminator
    // in real code you would check for errors in malloc here
    memcpy(result, s1, len1);
    memcpy(result + len1, s2, len2 + 1); // +1 to copy the null-terminator
    return result;
};