#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "str_handle.h"

char *remove_white_spaces(char *str, int len);
int valid_string(char *str);
int is_included_digit(char *str);
void str_to_lower(char *str);

Dept *create_dept_from_str(char *str)
{
    printf("%s\n", str);
    Dept *new = calloc(1, sizeof(Dept));
    char *value = strtok(str, ",");
    int column = 1;
    while (value)
    {
        //  check before creating for an char input into int,
        //  ex: -10u0, add to the int only the -10.

        switch (column)
        {
        case 1:
            // check if first name is valid
            // if invalid throw an error

            if (valid_string(value))
            {
                printf("not valid\n");
            }
            else
            {
                new->first_name = value;
            }
            break;
        case 2:
            // check if last name is valid
            value = remove_white_spaces(value, strlen(value) + 1);
            printf("valid? %s\n", valid_string(value) ? "no" : "yes");
            new->last_name = value;
            // strcpy(new->last_name, value);
            break;
        case 3:
            // check if id is valid
            new->id = atoi(value);
            break;
        case 4:
            // check if phone is valid
            new->phone = atoi(value);
            break;
        case 5:
            // check if dept is valid
            new->dept = atoi(value);
            break;
        case 6:
            // check if date is valid
            new->date = value;
            // strcpy(new->date, value);
            break;
        default:
            break;
        }
        column++;
        value = strtok(NULL, ",");
    }
    return new;
}

int valid_string(char *str)
{
    // before if(!*str) for a space only input
    str = remove_white_spaces(str, strlen(str) + 1);
    if (!*str)
    {
        return 1;
    }
    str_to_lower(str);
    return is_included_digit(str);
}

int valid_num(char *str)
{
    if (!str)
    {
        return 1;
    }
    str = remove_white_spaces(str, strlen(str) + 1);

    return is_included_digit(str);
}

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

int is_included_digit(char *str)
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

int is_only_digit(char *str)
{
    while (str)
    {
        if (str[0] != 32 && (str[0] > 127 || str[0] < 97))
        {
        }

        /* code */
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