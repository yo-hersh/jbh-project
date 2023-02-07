#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "DB.h"
#include "str_handling.h"

typedef struct _List
{
    Costumer costumer;
    struct _List *next;
} List;

typedef struct _BSTNode
{
    List *list;
    struct _BSTNode *right, *left;
} BSTNode;

static List *head = NULL, *tail = NULL;
static BSTNode *sort_by_id_root = NULL;
static BSTNode *sort_by_dept_root = NULL;

void comp_in_tree(BSTNode *root, Costumer *costumer, char *oper, PRINT_HANDLING print, int print_to);
int create_costumer(char *str, unsigned int line, PRINT_HANDLING print, int print_to);
void tree_in_order(BSTNode *root, void (*do_something)(Costumer *costumer, void *func, void *arg), void *func, void *arg);
int add_new(Costumer *new, PRINT_HANDLING print, int print_to);
void add_to_id_BST(BSTNode **root, List *list);
void add_to_dept_BST(BSTNode **root, List *list);
void add_dept_in_tail(Costumer *costumer);
void compare_str(char *str, char *oper, unsigned int index, PRINT_HANDLING print, int print_to);
int comp_values(Costumer *root, Costumer *costumer);
void add_date(char *str, Costumer *costumer);
void delete_dept_bst(BSTNode **root, int dept, unsigned int id);
int comp_date(Costumer *costumer_1, Costumer *costumer_2);
void free_all();
void free_tree(BSTNode *root);
void free_list(List *head);
BSTNode *max_bst(BSTNode *root);
Costumer *create_costumer_from_str(char *str, unsigned int line, PRINT_HANDLING print, int print_to);
Costumer *create_comp_costumer(char *str, unsigned int index, PRINT_HANDLING print, int print_to);
BSTNode *find_by_id(BSTNode *root, unsigned int id);

void create_list(FILE *file, PRINT_HANDLING print, int print_to)
{
    char buf[1024];
    unsigned int line = 0;
    while (fgets(buf, sizeof(buf), file))
    {
        if (buf[strlen(buf) - 1] == '\n')
        {
            buf[strlen(buf) - 1] = '\0';
        }
        create_costumer(buf, ++line, print, print_to);
    }
    fclose(file);
    print_all(print, print_to);
}

int create_costumer(char *str, unsigned int line, PRINT_HANDLING print, int print_to)
{
    Costumer *new = create_costumer_from_str(str, line, print, print_to);
    if (new)
    {
        return add_new(new, print, print_to);
    }
    return 1;
}

Costumer *create_costumer_from_str(char *str, unsigned int line, PRINT_HANDLING print, int print_to)
{
    Costumer *new = calloc(1, sizeof(Costumer));
    if (!new)
    {
        perror("error creating new dept");
        return NULL;
    }

    char line_str[30] = {0}, error_msg[200] = {0};
    if (line)
    {
        sprintf(&(line_str[0]), "error line %d: ", line);
    }

    str_to_lower(str);
    remove_white_spaces(str);
    
    char *value;
    value = strtok(str, ",");

    int is_error = 0, column = 1;
    for (int i = 0; i < 6 ; i++)
    {
        remove_white_spaces(value);
        switch (column)
        {
        case 1:
            if (valid_name(value))
            {
                new->first_name = calloc(strlen(value) + 1, sizeof(char));
                if (!new->first_name)
                {
                    perror("error creating first name");
                    return NULL;
                }

                strcpy(new->first_name, value);
            }
            else
            {
                sprintf((error_msg), "%sfirst name required to be letters only, at least 2\n", line_str);
                print(print_to, error_msg);
                is_error = 1;
            }
            break;
        case 2:
            if (valid_name(value))
            {
                new->second_name = calloc(strlen(value) + 1, sizeof(char));
                if (!new->second_name)
                {
                    perror("error creating last name");
                    return NULL;
                }
                strcpy(new->second_name, value);
            }
            else
            {
                sprintf((error_msg), "%ssecond name required to be letters only, at least 2\n", line_str);
                print(print_to, error_msg);
                is_error = 1;
            }
            break;
        case 3:
            if (valid_id(value))
            {
                new->id = atoi(value);
            }
            else
            {
                sprintf((error_msg), "%sid required to be 9 digits only\n", line_str);
                print(print_to, error_msg);
                is_error = 1;
            }
            break;
        case 4:
            if (valid_phone(value))
            {
                new->phone = atoi(value);
            }
            else
            {
                sprintf((error_msg), "%sphone required to be 10 digits only, start by 0\n", line_str);
                print(print_to, error_msg);
                is_error = 1;
            }
            break;
        case 5:
            if (valid_date(value))
            {
                add_date(value, new);
            }
            else
            {
                sprintf((error_msg), "%sdate required to be in dd/mm/yyyy format between 1970-2100\n", line_str);
                print(print_to, error_msg);
                is_error = 1;
            }
            break;
        case 6:
            if (valid_dept(value))
            {
                new->dept = atoi(value);
            }
            else
            {
                sprintf((error_msg), "%sdept required to be digits only\n", line_str);
                print(print_to, error_msg);
                is_error = 1;
            }
            break;
        }

        column++;
        value = strtok(NULL, ",");
    }
    if (value)
    {
        sprintf((error_msg), "%stoo many parameters\n", line_str);
        print(print_to, error_msg);
        is_error = 1;
    }
    if (is_error)
    {
        free(new->first_name);
        free(new->second_name);
        free(new);
        return NULL;
    }

    return new;
}

int add_new(Costumer *new, PRINT_HANDLING print, int print_to)
{
    int ret = 0;
    BSTNode *found = find_by_id(sort_by_id_root, new->id);

    if (!found)
    {
        add_dept_in_tail(new);
        add_to_id_BST(&sort_by_id_root, tail);
        add_to_dept_BST(&sort_by_dept_root, tail);
    }
    else
    {
        if (strcmp(found->list->costumer.first_name, new->first_name))
        {
            print(print_to, "the first name is not equal to the name in the DB\n");
            ret = 1;
            goto free;
        }

        if (strcmp(found->list->costumer.second_name, new->second_name))
        {
            print(print_to, "the second name is not equal to the name in the DB\n");
            ret = 1;
            goto free;
        }

        List *list = found->list;
        delete_dept_bst(&sort_by_dept_root, list->costumer.dept, list->costumer.id);
        list->costumer.dept += new->dept;
        list->costumer.phone = new->phone;
        if (comp_date(&(list->costumer), new) < 0)
        {
            list->costumer.date = new->date;
        }

        add_to_dept_BST(&sort_by_dept_root, list);
    free:
        free(new->first_name);
        free(new->second_name);
        free(new);
    }
    return ret;
}

void add_dept_in_tail(Costumer *costumer)
{
    List *new = calloc(1, sizeof(List));
    if (!new)
    {
        perror("error creating new list");
        return;
    }

    new->costumer = (*costumer);

    if (tail)
    {
        (tail)->next = new;
    }
    (tail) = new;
    free(costumer);

    if (!head)
    {
        head = tail;
    }
}

void add_to_id_BST(BSTNode **id_root, List *list)
{
    if (*id_root == NULL)
    {
        *id_root = calloc(1, sizeof(BSTNode));
        if (!id_root)
        {
            perror("error creating new id_bst");
            return;
        }

        (*id_root)->list = list;
        return;
    }

    if (list->costumer.id <= (*id_root)->list->costumer.id)
    {
        add_to_id_BST(&((*id_root)->left), list);
    }
    else
    {
        add_to_id_BST(&((*id_root)->right), list);
    }
}

void add_to_dept_BST(BSTNode **dept_root, List *list)
{
    if (*dept_root == NULL)
    {
        *dept_root = calloc(1, sizeof(BSTNode));
        if (!dept_root)
        {
            perror("error creating new dept_bst");
            return;
        }

        (*dept_root)->list = list;
        return;
    }

    if (list->costumer.dept <= (*dept_root)->list->costumer.dept)
    {
        add_to_dept_BST(&((*dept_root)->left), list);
    }
    else
    {
        add_to_dept_BST(&((*dept_root)->right), list);
    }
}

void tree_in_order(BSTNode *root, void (*do_something)(Costumer *costumer, void *func, void *arg), void *func, void *arg)
{
    if (!root)
    {
        return;
    }

    tree_in_order(root->left, do_something, func, arg);
    do_something(&(root->list->costumer), func, arg);
    tree_in_order(root->right, do_something, func, arg);
}

BSTNode *find_by_id(BSTNode *root, unsigned int id)
{
    if (!root)
    {
        return NULL;
    }

    if (root->list->costumer.id == id)
    {
        return root;
    }

    if (id > root->list->costumer.id)
    {
        return find_by_id(root->right, id);
    }
    else
    {
        return find_by_id(root->left, id);
    }
}

void compare_str(char *str, char *oper, unsigned int index, PRINT_HANDLING print, int print_to)
{
    Costumer *new = create_comp_costumer(str, index, print, print_to);
    if (new)
    {
        comp_in_tree(sort_by_dept_root, new, oper, print, print_to);
        free(new);
    }
}

Costumer *create_comp_costumer(char *str, unsigned int index, PRINT_HANDLING print, int print_to)
{
    Costumer *new = calloc(1, sizeof(Costumer));
    if (!new)
    {
        perror("error creating new dept to comp");
        return NULL;
    }

    switch (index)
    {
    case 0:
        if (valid_name(str))
        {
            new->first_name = str;
        }
        else                
        {
            print(print_to, "first name required to be letters only, at least 2\n");
            return NULL;
        }
        break;
    case 1:
        if (valid_name(str))
        {
            new->second_name = str;
        }
        else
        {
            print(print_to, "second name required to be letters only, at least 2\n");
            return NULL;
        }
        break;
    case 2:
        if (valid_id(str))
        {
            new->id = atoi(str);
        }
        else
        {
            print(print_to, "id required to be 9 digits only\n");
            return NULL;
        }
        break;
    case 3:
        if (valid_phone(str))
        {
            new->phone = atoi(str);
        }
        else
        {
            print(print_to, "phone required to be 10 digits only, start by 0\n");
            return NULL;
        }
        break;
    case 4:
        if (valid_date(str))
        {
            add_date(str, new);
        }
        else
        {
            print(print_to, "date required to be in dd/mm/yyyy format between 1970-2100\n");
            return NULL;
        }
        break;
    case 5:
        if (valid_dept(str))
        {
            new->dept = atoi(str);
        }
        else
        {
            print(print_to, "dept required to be digits only\n");
            return NULL;
        }
        break;
    }

    return new;
}

void comp_in_tree(BSTNode *root, Costumer *costumer, char *oper, PRINT_HANDLING print, int print_to)
{
    if (!root)
    {
        return;
    }

    comp_in_tree(root->left, costumer, oper, print, print_to);
    int ret = comp_values(&(root->list->costumer), costumer);
    if (strstr(oper, ">"))
    {
        if (ret > 0)
        {
            print_costumer(&(root->list->costumer), print, print_to);
        }
    }
    else if (strstr(oper, "<"))
    {
        if (ret < 0)
        {
            print_costumer(&(root->list->costumer), print, print_to);
        }
    }
    else if (strstr(oper, "!="))
    {
        if (ret != 0)
        {
            print_costumer(&(root->list->costumer), print, print_to);
        }
    }
    else if (strstr(oper, "="))
    {
        if (ret == 0)
        {
            print_costumer(&(root->list->costumer), print, print_to);
        }
    }

    comp_in_tree(root->right, costumer, oper, print, print_to);
}

int comp_int(int first, int second)
{
    if (first > second)
    {
        return 1;
    }
    else if (first < second)
    {
        return -1;
    }
    else
    {
        return 0;
    }
}

void add_date(char *str, Costumer *costumer)
{

    char  *ptr;

    char *value = strtok_r(str, "/", &ptr);
    int column = 1;
    while (value)
    {
        switch (column)
        {
        case 1:
            costumer->date.day = atoi(value);
            break;
        case 2:
            costumer->date.month = atoi(value);
            break;
        case 3:
            costumer->date.year = atoi(value);
            break;
        default:
            break;
        }
        value = strtok_r(NULL, "/", &ptr);
        column++;
    }
}

int comp_values(Costumer *root, Costumer *comp)
{
    if (comp->first_name)
    {
        return strcmp(root->first_name, comp->first_name);
    }
    else if (comp->second_name)
    {
        return strcmp(root->second_name, comp->second_name);
    }
    else if (comp->id)
    {
        return comp_int(root->id, comp->id);
    }
    else if (comp->phone)
    {
        return comp_int(root->phone, comp->phone);
    }
    else if (comp->dept)
    {
        return comp_int(root->dept, comp->dept);
    }
    else if (comp->date.year)
    {
        return comp_date(root, comp);
    }
}

int comp_date(Costumer *costumer_1, Costumer *costumer_2)
{
    int year = comp_int(costumer_1->date.year, costumer_2->date.year);
    if (year)
    {
        return year;
    }
    else
    {
        int month = comp_int(costumer_1->date.month, costumer_2->date.month);
        if (month)
        {
            return month;
        }
        else
        {
            return comp_int(costumer_1->date.day, costumer_2->date.day);
        }
    }
}

BSTNode *max_bst(BSTNode *root)
{
    if (root == NULL || root->right == NULL)
    {
        return root;
    }
    return max_bst(root->right);
}

void delete_dept_bst(BSTNode **root, int dept, unsigned int id)
{
    if (*root == NULL)
    {
        return;
    }

    if ((*root)->list->costumer.id == id && (*root)->list->costumer.dept == dept)
    {
        if ((*root)->left == NULL && (*root)->right == NULL)
        {
            free(*root);
            *root = NULL;
        }
        else if ((*root)->left != NULL && (*root)->right != NULL)
        {
            BSTNode *tmp = max_bst((*root)->left);
            (*root)->list = tmp->list;
            delete_dept_bst(&((*root)->left), tmp->list->costumer.dept, tmp->list->costumer.id);
        }
        else
        {
            BSTNode *tmp = (*root)->left ? (*root)->left : (*root)->right;
            free(*root);
            *root = tmp;
        }
    }
    else
    {
        if (dept <= (*root)->list->costumer.dept)
        {
            delete_dept_bst(&((*root)->left), dept, id);
        }
        else
        {
            delete_dept_bst(&((*root)->right), dept, id);
        }
    }
}

void print_all(PRINT_HANDLING print, int print_to)
{

    tree_in_order(sort_by_dept_root, print_costumer, (void *)print, (void *)print_to);
}

void free_all()
{
    free_tree(sort_by_dept_root);
    free_tree(sort_by_id_root);
    free_list(head);
}

void free_tree(BSTNode *root)
{
    if (!root)
    {
        return;
    }
    free_tree(root->right);
    free_tree(root->left);
    free(root);
}
void free_list(List *head)
{
    while (head)
    {
        List *temp = head->next;
        free(head->costumer.first_name);
        free(head->costumer.second_name);
        free(head);
        head = temp;
    }
}