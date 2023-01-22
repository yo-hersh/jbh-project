#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "DB.h"
#include "users_input.h"

int main(int argc, char const *argv[])
{

    if (argc < 2)
    {
        printf("Error: usage: %s <file name>\n", argv[0]);
        return 1;
    }

    FILE *file = fopen(argv[1], "r");

    // FILE *file = fopen("DB.csv", "r");
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
        else
        {

            user_str(buf);
        }

        // get input from user
        // user_manage
        // getstr(*str)

        // if str == exit
        //     call free_link()
        // break;
    }

    printf("see you, let's have a nice day\n");

    return 0;
}
