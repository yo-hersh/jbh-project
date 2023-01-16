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