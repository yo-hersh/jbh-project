#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "str_handling.h"

char *remove_white_spaces(char *str, int len);
void str_to_lower(char *str);
int valid_date(char *str);
int valid_dept(char *str);
int valid_phone(char *str);
int valid_id(char *str);
int valid_name(char *str);
int is_not_only_digit(char *str);
int is_not_only_char(char *str);

// void add_to_error_str(char *error_str, int line_num, char *value);
// void print_err(char *str, int line);

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
}

int valid_id(char *str)
{
    if (!str)
    {
        return 0;
    }

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

// char *stringify_costumer(Costumer *costumer)
// {

//     unsigned int len = strlen(costumer->first_name) + strlen(costumer->last_name) + strlen(itoa(costumer->dept) + 40);

//     char *f_name = costumer->first_name;
//     char *l_name = costumer->last_name;
//     char *id = itoa(costumer->id);
//     char *phone = itoa(costumer->phone);
//     char *dept = itoa(costumer->dept);
//     char *year = costumer->date.year;
//     char *month = costumer->date.month;
//     char *day = costumer->date.day;
//     char *ret = malloc(strlen(f_name) + strlen(s_name) + strlen(id) + strlen(phone) + strlen(dept) + strlen(year) + strlen(mount) + strlen(day) + 10);
//     int i = 0, j = 0;
//     while (f_name[i] != '\0')
//     {
//         ret[j++] = f_name[i++];
//     }
//     ret[j++] = ' ';
//     ret[j++] = ',';
//     i = 0;
//     while (l_name[i] != '\0')
//     {
//         ret[j++] = l_name[i++];
//     }
//     ret[j++] = ' ';
//     ret[j++] = ',';
//     i = 0;
//     while (id[i] != '\0')
//     {
//         ret[j++] = id[i++];
//     }
//     ret[j++] = ' ';
//     ret[j++] = ',';
//     i = 0;
//     while (phone[i] != '\0')
//     {
//         ret[j++] = phone[i++];
//     }
//     ret[j++] = ' ';
//     ret[j++] = ',';
//     i = 0;
//     while (dept[i] != '\0')
//     {
//         ret[j++] = dept[i++];
//     }
//     ret[j++] = ' ';
//     ret[j++] = ',';
//     i = 0;
//     while (year[i] != '\0')
//     {
//         ret[j++] = year[i++];
//     }
//     ret[j++] = ' ';
//     ret[j++] = ',';
//     i = 0;
//     while (month[i] != '\0')
//     {
//         ret[j++] = month[i++];
//     }
//     ret[j++] = ' ';
//     ret[j++] = ',';
//     i = 0;
//     while (day[i] != '\0')
//     {
//         ret[j++] = day[i++];
//     }
//     ret[j++] = ' ';
//     ret[j++] = ',';
//     return ret;
// }

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

void print_err(char *str, int line)
{
    printf("error");
    if (line)
    {
        printf("line %d", line);
    }
    printf(": %s\n", str);
}

char *concat(const char *s1, const char *s2)
{
    int len1 = strlen(s1);
    int len2 = strlen(s2);
    char *result = malloc(len1 + len2 + 1); // +1 for the null-terminator
    // in real code you would check for errors in malloc here
    memcpy(result, s1, len1);
    memcpy(result + len1, s2, len2 + 1); // +1 to copy the null-terminator
    return result;
}