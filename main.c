#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "DB.h"

int main(int argc, char const *argv[])
{

    if (argc < 2)
    {
        printf("Error: usage: %s <file name>\n", argv[0]);
        return 1;
    }

    FILE *file = fopen(argv[1], "r");

    FILE *file = fopen(file, "r");
    if (!file)
    {
        printf("Error: file %s not found\n", argv[1]);
        return 1;
    }

    create_list(file);
    while (1)
    {
        // get input from user
        // user_manage
        // getstr(*str)

        // if str == exit
        //     call free_link()
        // break;
    }

    return 0;
}
