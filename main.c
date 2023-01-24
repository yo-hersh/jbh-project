#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "DB.h"
#include "users_input.h"

int main(int argc, char const *argv[])
{

    char *display_option = "please select option: set <value>, select <value>, print.\n use <option> --help to see more.";
    char *select_help = "select <value> <operation> <everything>.\n";
    char *set_help = "set <value> = <everything>.\n";
    char *values_help = "values: first name, last name, id, phone, dept, date.\n";
    char *error_msg[1024] = {0};

    if (argc < 2)
    {
        printf("Error: usage: %s <file name>\n", argv[0]);
        return 1;
    }

    FILE *file = fopen(argv[1], "r");

    if (!file)
    {
        printf("Error: file %s not found\n", argv[1]);
        return 1;
    }

    create_list(file);
    char buf[200] = {0};
    while (1)
    {
        fgets(buf, sizeof(buf), stdin);
        if (!strcmp(buf, "quit\n"))
        {
            break;
        }
        if (!strcmp(buf, "print\n"))
        {
            print();
        }
        else
        {
            if (buf[0])
            {
                int ret = user_str(buf, error_msg);
            }
            if (ret)
            {
                printf("%s", error_msg);
            }
        }
    }

    printf("see you, let's have a nice day\n");

    return 0;
}
