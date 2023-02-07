#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "users_input.h"
#include "DB.h"
#include "str_handling.h"

#define ARR_LEN(arr) (sizeof(arr) / sizeof(arr[0]))

const char *values_arr[] = {"first name", "second name", "id", "phone", "date", "debt"};
const char *oper_arr[] = {">", "<", "!=", "="};
const char *options_arr[] = {"select", "set"};

void select_handling(char *str, PRINT_HANDLING print, int print_to);
void set_handling(char *str, PRINT_HANDLING print, int print_to);

void user_str(char *str, PRINT_HANDLING print, int print_to)
{
    str_to_lower(str);
    remove_white_spaces(str);
    for (int i = 0; i < ARR_LEN(options_arr); i++)
    {
        unsigned int len = strlen(options_arr[i]);
        if (!memcmp(str, options_arr[i], len))
        {
            switch (i)
            {
            case 0:
                str += len;
                select_handling(str, print, print_to);
                break;
            case 1:
                str += len;
                set_handling(str, print, print_to);
                break;
            default:
                print(print_to, "invalid used. use: set / select / print only\n");
                break;
            }
        }
    }
}

void select_handling(char *str, PRINT_HANDLING print, int print_to)
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
        print(print_to, "use one of the given values only\n");
        return;
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
        print(print_to, "used oper: = != < > only\n");
        return;
    }

    remove_white_spaces(str);
    compare_str(str, oper, i, print, print_to);

    return;
}

void set_handling(char *str, PRINT_HANDLING print, int print_to)
{
    int ret;
    char *values = calloc(strlen(str), sizeof(char));
    if (!values)
    {
        perror("error creating values str");
        return;
    }

    if (*str == '\n')
    {
        print(print_to, "invalid value\n");
        goto exit;
    }

    if (*str == ' ')
    {
        str++;
    }

    char *value = strtok(str, ",");
    char error_msg[50] = {0};

    for (int i = 0; i < ARR_LEN(values_arr); i++)
    {
        if (!value)
        {
            sprintf(error_msg, "value <%s> dont found\n", values_arr[i]);
            print(print_to, error_msg);
            goto exit;
        }

        remove_white_spaces(value);
        unsigned int len = strlen(values_arr[i]);
        if (memcmp(value, values_arr[i], len))
        {
            sprintf((error_msg), "value <%s> dont found\n", values_arr[i]);
            print(print_to, error_msg);
            goto exit;
        }
        value += len;
        if (*value == ' ')
        {
            value++;
        }

        if (*value != '=')
        {
            sprintf((error_msg), "invalid operation\n");
            print(print_to, error_msg);
            goto exit;
        }

        value++;

        int values_len = strlen(values);
        sprintf(&(values[values_len]), "%s,", value);
        value = strtok(NULL, ",");
    }

    ret = create_costumer(values, 0, print, print_to);
    if (ret)
    {
        print(print_to, "debt creation is not complete\n");
    }
    else
    {
        print(print_to, "created successfully\n");
    }

exit:
    free(values);
    return;
}