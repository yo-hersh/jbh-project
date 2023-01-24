#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "users_input.h"
#include "DB.h"
#include "str_handling.h"

#define ARR_LEN(arr) (sizeof(arr) / sizeof(arr[0]))

const char *values_arr[] = {"first name", "last name", "id", "phone", "dept", "date"};
const char *oper_arr[] = {">", "<", "!=", "="};
const char *options_arr[] = {"select", "set"};

int select_handling(char *str, char *error_msg);
int set_handling(char *str, char *error_msg);
Costumer *create_comp_costumer(char *str, int index);

int user_str(char *str, char *error_msg)
{
    str_to_lower(str);
    str = remove_white_spaces(str, strlen(str) + 1);
    int ret;
    for (int i = 0; i < ARR_LEN(options_arr); i++)
    {
        unsigned int len = strlen(options_arr[i]);
        if (!memcmp(str, options_arr[i], len))
        {
            switch (i)
            {
            case 0:
                str += len;
                return select_handling(str, error_msg);
                break;
            case 1:
                str += len;
                return set_handling(str, error_str);
                break;
            default:
                sprintf(&(error_msg[strlen(error_msg)]), "invalid used. use: set / select / print only\n");
                return 1;
                break;
            }
        }
    }
}

int select_handling(char *str, char *error_msg)
{
    char value[10] = {0}, oper[3] = {0};
    int i;
    while (*str == ' ')
    {
        str++;
    }

    for (i = 0; i < ARR_LEN(values_arr); i++)
    {
        unsigned int len = strlen(values_arr[i]);
        if (!memcmp(str, values_arr[i], len))
        {
            str += len;
            strcpy(value, values_arr[i]);
            break;
        }
    }
    if (i == ARR_LEN(values_arr))
    {
        sprintf(&(error_msg[strlen(error_msg)]), "use one of the given values only\n");
        return 1;
    }

    if (*str == ' ')
        str++;

    int j = 0;

    for (; j < ARR_LEN(oper_arr); j++)
    {
        unsigned int len = strlen(oper_arr[j]);
        if (!memcmp(str, oper_arr[j], len))
        {
            str += len;
            strcpy(oper, oper_arr[j]);
            break;
        }
    }
    if (j == ARR_LEN(oper_arr))
    {
        sprintf(&(error_msg[strlen(error_msg)]), "used oper: = != < > only\n");
        return 1;
    }

    str = remove_white_spaces(str, strlen(str) + 1);
    char *return_str = compare_2(str, i, error_msg);
    // its the real way???
    if (*error_msg)
    {
        return 1;
    }

    if (*return_str)
    {
        printf("found:\n%s", return_str);
    }
    else
    {
        printf("nothing found\n")
    }

    // Costumer *new = create_comp_costumer(str, i);
    // if (new)
    // {
    // char *return_str = compare(new, oper);
    // if (*return_str)
    // {
    // printf("%s", return_str);
    // }
    // }
    // else
    // {
    //     /* code */
    // }

    return 0;
}

int set_handling(char *str, char *error_msg)
{
    char *values = calloc(1, strlen(str) * sizeof(char));
    if (values)
    {
        /* code */
    }

    unsigned int curr = 0;
    if (*str == '\n')
    {
        sprintf(&(error_msg[strlen(error_msg)]), "invalid value\n");
        return 1;
    }

    if (*str == ' ')
    {
        str++;
    }

    char *value = strtok(str, ",\n");
    for (int i = 0; i < ARR_LEN(values_arr); i++)
    {
        value = remove_white_spaces(value, strlen(value));
        unsigned int len = strlen(values_arr[i]);
        if (memcmp(value, values_arr[i], len))
        {
            return 1;
        }
        value += len;

        if (*value != '=')
        {
            sprintf(&(error_msg[strlen(error_msg)]), "invalid operation\n");
            return 1;
        }

        // למה משמש?
        value++;

        int v_len = strlen(value);
        if (value[v_len] == '\n')
        {
            value[v_len] = '\0';
        }

        // יש תצורך???
        int values_len = strlen(values);
        sprintf(&(values[values_len]), "%s,", value);
        value = strtok(NULL, ",\n");
    }

    return create_costumer(values, 0, error_msg);
}