#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "str_handling.h"
#include "DB.h"
#include "users_input.h"

int main(int argc, char const *argv[])
{
    char *display_option = "\n--please select option: set <value> / select <value> / print\n--use <option> --help to see more\n--type quit to exit\n";
    char *select_help = "--select <value> <operation> <everything>.\n";
    char *set_help = "--set <value> = <everything>.\n";
    char *values_help = "--values: first name, last name, id, phone, date, debt.\n";

    if (argc < 2)
    {
        printf("Usage: %s <db file>\n", argv[0]);
        return EXIT_FAILURE;
    }

    FILE *file = fopen(argv[1], "r");

    if (!file)
    {
        printf("Error: file %s not found\n", argv[1]);
        return EXIT_FAILURE;
    }

    create_list(file);
    char buf[200] = {0};
    while (1)
    {
        printf("%s", display_option);
        fgets(buf, sizeof(buf), stdin);
        if (!strcmp(buf, "quit\n"))
        {
            break;
        }
        if (!strcmp(buf, "print\n"))
        {
            print_all(print_to_stdout, 0);
        }
        else if (!strcmp(buf, "set --help\n"))
        {
            printf("%s%s", set_help, values_help);
        }
        else if (!strcmp(buf, "select --help\n"))
        {
            printf("%s%s", select_help, values_help);
        }
        else
        {
            if (buf_overflow(buf, print_to_stdout, 0))
            {
                continue;
            }
            if (buf[0])
            {
                user_str(buf, print_to_stdout, 0);
            }
        }
    }

    printf("see you, let's have a nice day\n");
    free_all();
    return EXIT_SUCCESS;
}

// // socket_id is not using, only for network program - as a ref func
// void print_to_stdout(int socket_id, char *str)
// {
//     printf("%s", str);
// }