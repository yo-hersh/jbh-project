#include "str_handle.h"

Dept *create_dept_from_str(char *str)
{
    printf("%s\n", str);
    Dept *new = calloc(1, sizeof(Dept));
    char *value = strtok(str, ", ");
    int column = 1;
    while (value)
    {
        //  check after creating?
        switch (column)
        {
        case 1:
            // check if first name is valid
            // if invalid throw an error
            strcpy(new->first_name, value);
            break;
        case 2:
            // check if last name is valid
            strcpy(new->last_name, value);
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
            strcpy(new->date, value);
            break;
        default:
            break;
        }
        column++;
        value = strtok(NULL, ",");
    }
    return new;
}

int valid_values(Dept *new)
{
}

char *remove_white_spaces(char *str, int len)
{
    int i = 0, j = 0;
    char *new_str = calloc(len +1 ,sizeof(char));

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