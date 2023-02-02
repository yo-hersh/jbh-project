#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "DB.h"
#include "users_input.h"

void print_to_stdin(int socket_id, char *str);

int main(int argc, char const *argv[])
{

    char *display_option = "\n--please select option: set <value> / select <value> / print\n--use <option> --help to see more\n--type quit to exit\n";
    char *select_help = "--select <value> <operation> <everything>.\n";
    char *set_help = "--set <value> = <everything>.\n";
    char *values_help = "--values: first name, last name, id, phone, dept, date.\n";

    if (argc < 2)
    {
        return 1;
    }

    FILE *file = fopen(argv[1], "r");

    if (!file)
    {
        printf("Error: file %s not found\n", argv[1]);
        return 1;
    }

    create_list(file, print_to_stdin, 0);
    char buf[200] = {0};
    while (1)
    {
        printf("%s", display_option);
        fgets(buf, sizeof(buf), stdin);
        if (!strcmp(buf, "quit\n"))
        {
            break;
        }
        else if (!strcmp(buf, "print\n"))
        {
            print_all(print_to_stdin,0);
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
            if (buf[strlen(buf) - 1] == '\n')
            {
                buf[strlen(buf) - 1] = '\0';
            }
            if (buf[0])
            {
                user_str(buf, print_to_stdin, 0);
            }
        }
    }

    printf("see you, let's have a nice day\n");
    free_all();
    return 0;
}

void print_to_stdin(int socket_id, char *str)
{
    printf("%s", str);
}