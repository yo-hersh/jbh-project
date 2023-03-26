#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <signal.h>
#include "str_handling.h"
#include "DB.h"
#include "users_input.h"

void int_handler(int sig);

int main(int argc, char const *argv[])
{
    signal(SIGINT, int_handler);

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
        printf("%s", massage);
        fgets(buf, sizeof(buf), stdin);
        if (!strcmp(buf, "quit\n"))
        {
            break;
        }
        if (!strcmp(buf, "halp"))
        {
            printf("%s", display_option);
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
                input_handling(buf, print_to_stdout, 0);
            }
        }
    }

    printf("See you, thanks for using the DB program\n");
    free_all();
    return EXIT_SUCCESS;
}

void int_handler(int sig)
{
    free_all();
    printf("\nexiting....\n");
    exit(0);
}