#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "users_input.h"
#include "DB.h"
#include "str_handle.h"

#define ARR_LEN(arr) (sizeof(arr) / sizeof(arr[0]))

const char *values_arr[] = { "first name", "last name", "id", "phone", "dept", "date" };
const char *oper_arr[] = { ">", "<", "!=", "==" };
const char *options_arr[] = { "select", "set" };

int select_handling(char *str);


void user_str(char *str)
{
    char *error_str = NULL;
    char *value = strtok(str, ",");
    str_to_lower(str);
    str = remove_white_spaces(str, strlen(str) + 1);
    // void *p_option_func = NULL;
    void *p_oper_func = NULL;
    for (int i = 0; i < ARR_LEN(options_arr); i++)
    {
        unsigned int len = strlen(values_arr[i]);
        if (!memcmp(str, values_arr[i], len))
        {
            switch (i)
            {
            case 0:
                // goto select not in the same function
                str += len + 1;
                // select_handling(str);
                break;
            case 1:
                str += len;
                // set_handling(str);
                // p_option_func = set_func;
                break;
            default:
                // error
                break;
            }
        }
    }

    // for (int i = 0; i < ARR_LEN(values_arr); i++)
    // {
    //     unsigned int len = strlen(values_arr[i]);
    //     if (!memcmp(str, values_arr[i], len))
    //     {
    //         switch (i)
    //         {
    //         case 0:
    //             p_oper_func = greeter_from;
    //             str += len;
    //             break;
    //         case 1:
    //             p_oper_func = smaller_from;
    //             str += len;
    //             break;
    //         case 2:
    //             p_oper_func = not_equal;
    //             str += len;
    //             break;
    //         case 3:
    //             p_oper_func = equal_to;
    //             str += len;
    //             break;
    //         default:
    //             // error
    //             break;
    //         }
    //         switch (i)
    //         {
    //         case 1:
    //             /* code */
    //             break;

    //         default:
    //             break;
    //         }
    //         /* code */
    //     }

    //     /* code */
    // }

    // for (int i = 0; i < strlen(str); i++)
    // {
    //     if (str[i] != '=' && str[i] != '<')
    //     {
    //         /* code */
    //     }

    //     /* code */
    // }

    int ret = NULL;

    // while (str != ' ')
    // {
    //     value += str++;
    // }

    // if (!strcmp(value, "select"))
    // {
    //     ret = select_handling(char *str)

    //     /* code */
    // }
    // else if (!strcmp(value, "set"))
    // {

    //     /* code */
    // }
};

// int select_handling(char *str)
// {
//     void *p_value_func = NULL;
//     void *p_oper_func = NULL;

//     for (int i = 0; i < ARR_LEN(values_arr); i++)
//     {
//         unsigned int len = strlen(values_arr[i]);
//         char value[len] = {0};
//         if (!memcmp(str, values_arr[i], len))
//         {
//             str += len;
//             value = values_arr[i];
//         }
//     }

//     for (int i = 0; i < ARR_LEN(oper_arr); i++)
//     {
//         unsigned int len = strlen(oper_arr[i]);
//         if (!memcmp(str, oper_arr[i], len))
//         {
//             switch (i)
//             {
//             case 0:
//                 p_oper_func = greeter_from;
//                 str += len;
//                 break;
//             case 1:
//                 p_oper_func = smaller_from;
//                 str += len;
//                 break;
//             case 2:
//                 p_oper_func = not_equal;
//                 str += len;
//                 break;
//             case 3:
//                 p_oper_func = equal_to;
//                 str += len;
//                 break;
//             default:
//                 // error
//                 break;
//             }
//         }
//     }
    // delete first space
    // str++;

//     for (int i = 0; i < ARR_LEN(values_arr); i++)
//     {
//         if (!strstr(str, values_arr[i]))
//         {
//             str += sizeof(values_arr[i]);
//             select_by(str, values_arr[i]);
//         }
//     }
// }

// typedef Costumer *(*COMP_VALUE)(Costumer *dept, char *value)
// {
//     switch (value)
//     {
//     case "first name":
//         return costumer.first_name;
//     case "last name":
//         return costumer.last_name;
//     case "id":
//         return costumer.id;
//     case "phone":
//         return costumer.phone;
//     case "dept":
//         return costumer.dept;
//     case "date":
//         return costumer.data;
//     default:
//         break;
//     }
// }

// int (*greeter_from)(COMP_VALUE comp_value, char *value)
// {
//     return comp_value() > value;
// }

// void select_by(char *str, char *value)
// {
//     while (str != ' ')
//     {
//         /* code */
//     }
// }

// char *opr_found(char *str)
// {
//     if (str[0] == '=' !str[0] == '!' !str[0] == '<' !str[0] == '>')
//     {
//         return &str[0];
//         /* code */
//     }
//     return NULL;
// }