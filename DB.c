#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "DB.h"
#include "str_handling.h"

// לבדוק שההקצאה הצליחה

typedef struct _List
{
    Costumer costumer;
    struct _List *next;
} List;

// a binary tree
// using to get indexes
// wee creating a tree to index the costumer sum and the id
typedef struct _BSTNode
{
    List *list;
    struct _BSTNode *right, *left;
} BSTNode;

List *head = NULL, *tail = NULL;
BSTNode *sort_by_id_root = NULL;
BSTNode *sort_by_dept_root = NULL;

void tree_in_order(BSTNode *root, void (*do_something)(Costumer *costumer));
void add_new(Costumer *new);
void add_to_id_BST(BSTNode **root, List *list);
void add_to_dept_BST(BSTNode **root, List *list);
void add_dept_in_tail(Costumer *costumer);
List *find_by_id(BSTNode *root, int id);
void comp_in_tree(BSTNode *root, Costumer *costumer, char *oper, char *arr);
void add_to_arr(void *arr, Costumer *costumer);
void delete_from_bst(BSTNode **root);
BSTNode *max_bst(BSTNode *root);
BSTNode *find_by_id_2(BSTNode *root, int id);
// BSTNode *find_by_dept_id(BSTNode *root, int dept, int id);
char *compare(Costumer *costumer, char *oper);
int func_to_comp(Costumer *root, Costumer *costumer);
int add_date(char *str, Costumer *costumer);
Costumer *create_costumer_from_str(char *str, int line, char *error_msg);
void delete(BSTNode **root, int dept, int id);
void print();

void create_list(FILE *file)
{
    char buf[100];
    int line = 0;
    while (fgets(buf, sizeof(buf), file))
    {
        char error_msg[1024];
        int ret = create_costumer(buf, ++line, error_msg);
        if (ret)
        {
            printf("%s", error_msg);
        }
    }
    print();
}

int create_costumer(char *str, int line, char *error_msg)
{
    Costumer *new = create_costumer_from_str(str, line, error_msg);
    if (new)
    {
        add_new(new);
        return 0;
    }
    return 1;
}

Costumer *create_costumer_from_str(char *str, int line, char *error_msg)
{
    Costumer *new = calloc(1, sizeof(Costumer));
    if (!new)
    {
        /* code */
    }

    int is_error = 0;
    str_to_lower(str);
    str = remove_white_spaces(str, strlen(str) + 1);

    char *value = strtok(str, ",");
    int column = 1;
    while (value)
    {
        value = remove_white_spaces(value, strlen(str) + 1);
        switch (column)
        {
        case 1:
            if (valid_name(value))
            {
                new->first_name = value;
            }
            else
            {
                sprintf(&(error_msg[strlen(error_msg)]), "first name must have only char, last tow\n");
                is_error = 1;
            }
            break;
        case 2:
            if (valid_name(value))
            {
                new->last_name = value;
            }
            else
            {
                sprintf(&(error_msg[strlen(error_msg)]), "last name must have only char, last tow\n");
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
                sprintf(&(error_msg[strlen(error_msg)]), "id must have only 9 digits\n");
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
                sprintf(&(error_msg[strlen(error_msg)]), "phone must have only 10 digits, start by 0\n");
                is_error = 1;
            }
            break;
        case 5:
            if (valid_dept(value))
            {
                new->dept = atoi(value);
            }
            else
            {
                sprintf(&(error_msg[strlen(error_msg)]), "dept must have digits only\n");
                is_error = 1;
            }
            break;
        case 6:
            if (!valid_date(value))
            {
                add_date(value, new);
            }
            else
            {
                sprintf(&(error_msg[strlen(error_msg)]), "date must by dd/mm/yyyy between 1970-2100\n");
                is_error = 1;
            }
            break;
        }
        column++;
        value = strtok(NULL, ",");
    }
    if (is_error)
    {
        return NULL;
    }

    return new;
}

void add_new(Costumer *new)
{
    // List *found = find_by_id(sort_by_id_root, new->id);

    // if (found == NULL)
    // {
    //     add_dept_in_tail(new);
    //     add_to_id_BST(&sort_by_id_root, tail);
    //     add_to_dept_BST(&sort_by_dept_root, tail);
    // }
    // else
    // {
    //     if (strcmp(found->costumer.first_name, new->first_name))
    //     {
    //         printf("first name is not equal to the name in the DB\n");
    //         goto free;
    //     }

    //     if (strcmp(found->costumer.last_name, new->last_name))
    //     {
    //         printf("last name is not equal to the name in the DB\n");
    //         goto free;
    //     }

    //     found->costumer.dept += new->dept;
    //     found->costumer.phone = new->phone;
    //     found->costumer.date = new->date;;

    BSTNode *found = find_by_id_2(sort_by_id_root, new->id);

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
            printf("first name is not equal to the name in the DB\n");
            goto free;
        }

        if (strcmp(found->list->costumer.last_name, new->last_name))
        {
            printf("last name is not equal to the name in the DB\n");
            goto free;
        }

        List *list = found->list;
        delete (&sort_by_dept_root, list->costumer.dept, list->costumer.id);
        list->costumer.dept += new->dept;
        list->costumer.phone = new->phone;
        list->costumer.date = new->date;

        // found = find_by_dept_id(sort_by_dept_root, list->costumer.dept, list->costumer.id);
        // delete_from_bst(&found);
        add_to_dept_BST(&sort_by_dept_root, list);
        // memcpy(found->costumer.date, new->date,sizeof(Date));
    free:
        free(new);
    }
    // tree_in_order(sort_by_dept_root, print_costumer);
}

void add_dept_in_tail(Costumer *costumer)
{
    List *new = calloc(1, sizeof(List));
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
        (*id_root)->list = list;
        return;
    }

    if ((*id_root)->list->costumer.id > list->costumer.id)
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
        (*dept_root)->list = list;
        return;
    }

    if ((*dept_root)->list->costumer.dept > list->costumer.dept)
    {
        add_to_dept_BST(&((*dept_root)->left), list);
    }
    else
    {
        add_to_dept_BST(&((*dept_root)->right), list);
    }
}

void tree_in_order(BSTNode *root, void (*do_something)(Costumer *costumer))
{
    if (!root)
    {
        return;
    }

    tree_in_order(root->left, do_something);
    do_something(&(root->list->costumer));
    tree_in_order(root->right, do_something);
}

// List *find_by_id(BSTNode *root, int id)
// {
//     if (!root)
//     {
//         return NULL;
//     }

//     if (root->list->costumer.id == id)
//     {
//         return root->list;
//     }

//     if (id > root->list->costumer.id)
//     {
//         return find_by_id(root->right, id);
//     }
//     else
//     {
//         return find_by_id(root->left, id);
//     }
// }

BSTNode *find_by_id_2(BSTNode *root, int id)
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
        return find_by_id_2(root->right, id);
    }
    else
    {
        return find_by_id_2(root->left, id);
    }
}

// BSTNode *find_by_dept_id(BSTNode *root, int dept, int id)
// {
//     if (!root)
//     {
//         return NULL;
//     }

//     if (root->list->costumer.id == id && root->list->costumer.dept == dept)
//     {
//         return root;
//     }

//     if (dept > root->list->costumer.dept)
//     {
//         return find_by_dept_id(root->right, dept, id);
//     }
//     else
//     {
//         return find_by_dept_id(root->left, dept, id);
//     }
// }

char *compare_2(char *str, int index, char *error_msg)
{
    Costumer *new = create_comp_costumer(str, i, error_msg);
    if (new)
    {
        return compare(new, oper);
    }
}

Costumer *create_comp_costumer(char *str, int index, char *error_msg)
{
    Costumer *new = calloc(1, sizeof(Costumer));
    if (!new)
    {
        // peeror
    }
    int is_error = 0;

    switch (index)
    {
    case 0:
        if (valid_name(str))
        {
            new->first_name = str;
        }
        else
        {
            sprintf(&(error_msg[strlen(error_msg)]), "first name must have only char, last tow\n");
            return 1;
        }
        break;
    case 1:
        if (valid_name(str))
        {
            new->last_name = str;
        }
        else
        {
            sprintf(&(error_msg[strlen(error_msg)]), "last name must have only char, last tow\n");
            return 1;
        }
        break;
    case 2:
        if (valid_id(str))
        {
            new->id = atoi(str);
        }
        else
        {
            sprintf(&(error_msg[strlen(error_msg)]), "id must have 9 digit\n");
            return 1;
        }
        break;
    case 3:
        if (valid_phone(str))
        {
            new->phone = atoi(str);
        }
        else
        {
            sprintf(&(error_msg[strlen(error_msg)]), "phone most have 10 char, starting by 0\n");
            return 1;
        }
        break;
    case 4:
        if (valid_dept(str))
        {
            new->dept = atoi(str);
        }
        else
        {
            sprintf(&(error_msg[strlen(error_msg)]), "dept must have only digit\n");
            return 1;
        }
        break;
    case 5:
        if (!valid_date(str))
        {
            add_date(str, new);
            // printf("%serror: last name not in the real format\n", line_str);
            is_error = 1;
        }
        else
        {
            sprintf(&(error_msg[strlen(error_msg)]), "date must by dd/mm/yyyy between 1970-2100\n");
            return 1;
        }
        break;
    default:
        return 1;
    }

    return new;
}

char *compare(Costumer *costumer, char *oper)
{
    char *arr = calloc(1, sizeof(char));
    comp_in_tree(sort_by_dept_root, costumer, oper, arr);
    return arr;
}

void comp_in_tree(BSTNode *root, Costumer *costumer, char *oper, char *arr)
{
    if (!root)
    {
        return;
    }

    comp_in_tree(root->left, costumer, oper, arr);
    int ret = func_to_comp(&(root->list->costumer), costumer);
    if (strstr(oper, ">"))
    {
        if (ret > 0)
        {
            add_to_arr(arr, &(root->list->costumer));
        } /* code */
    }
    else if (strstr(oper, "<"))
    {
        if (ret < 0)
        {
            add_to_arr(arr, &(root->list->costumer));
        } /* code */
        /* code */
    }
    else if (strstr(oper, "!="))
    {
        if (ret != 0)
        {
            add_to_arr(arr, &(root->list->costumer));
        } /* code */
        /* code */
    }
    else if (strstr(oper, "="))
    {
        if (ret == 0)
        {
            add_to_arr(arr, &(root->list->costumer));
        } /* code */
        /* code */
    }

    // switch (oper)
    // {
    // case '>':

    //     if (ret > 0)
    //     {
    //         add_to_arr(arr, root);
    //     }
    //     break;
    // case '<':
    //     if (ret < 0)
    //     {
    //         add_to_arr(arr, root);
    //     }
    //     break;
    // case '==':
    //     if (ret == 0)
    //     {
    //         add_to_arr(arr, root);
    //     }
    //     break;
    // case '!=':
    //     if (ret != 0)
    //     {
    //         add_to_arr(arr, root);
    //     }
    //     break;
    // }
    comp_in_tree(root->right, costumer, oper, arr);
}

void add_to_arr(void *arr, Costumer *costumer)
{
    // get the ral len from the stringify
    unsigned int len = strlen(costumer->first_name) + strlen(costumer->last_name) + 40;
    unsigned int curr = strlen(arr);
    arr = realloc(arr, (curr + len) * sizeof(char));
    stringify_costumer(costumer, (arr + curr), len, curr);
    // int len = strlen(arr);
    // char *ret = stringify_costumer(costumer);
    // int i = 0;
    // while (ret[i] != '\0')
    // {
    //     arr[len++] = ret[i++];
    // }
    // arr[len] = '\n';
    // free(ret);
}

int comp_int(int first, int second)
{
    if (first > second)
    {
        1;
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

// void func_in_tree(BSTNode *root, char *value, char *oper, char *str, char *return_str)
// {
//     if (!root)
//     {
//         return;
//     }

//     func_in_tree(root->left, value, oper, str, return_str);

//     switch (oper)
//     {
//     case '>':
//         if (ret > 0)
//         {
//             strcpy()
//                 add_to_arr(arr, root, arr_length);
//         }
//         break;
//     case '<':
//         if (ret < 0)
//         {
//             add_to_arr(arr, root, arr_length);
//         }
//         break;
//     case '==':
//         if (ret == 0)
//         {
//             add_to_arr(arr, root, arr_length);
//         }
//         break;
//     case '!=':
//         if (ret != 0)
//         {
//             add_to_arr(arr, root, arr_length);
//         }
//         break;
//     }
//     // printf("%s %s, costumer: %d\n", root->list->costumer.first_name, root->list->costumer.last_name, root->list->costumer.dept);
//     func_in_tree(root->right, value, oper, str, return_str);
// }

// char *comp_(char *value, char *oper, char *str)
// {
//     char *return_str = NULL;
//     func_in_tree(sort_by_dept_root, value, oper, str, return_str);
// }

int add_date(char *str, Costumer *costumer)
{
    if (!str)
    {
        return 0;
    }

    int day, month, year;
    char *value = strtok(str, "/");
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
        value = strtok(NULL, "/");
        column++;
    }
    return 1;
}

int func_to_comp(Costumer *root, Costumer *comp)
{
    if (comp->first_name)
    {
        // ?????
        // return strstr(root->first_name, comp->first_name);
        return strcmp(root->first_name, comp->first_name);
    }
    else if (comp->last_name)
    {
        return strcmp(root->last_name, comp->last_name);
    }
    else if (comp->id)
    {
        return comp_int(root->id, comp->id);
    }
    else if (comp->phone)
    {
        return comp_int(root->phone, comp->phone);

        // return memcmp(root->phone, comp->phone, strlen(root->phone));
    }
    else if (comp->dept)
    {
        return comp_int(root->dept, comp->dept);
        // return memcmp(root->dept, comp->dept, strlen(root->dept));
    }
    else if (comp->date.year)
    {
        int year = comp_int(root->date.year, comp->date.year);
        if (year)
        {
            return year;
        }
        else
        {
            int month = comp_int(root->date.month, comp->date.month);
            if (month)
            {
                return month;
            }
            else
            {
                return comp_int(root->date.day, comp->date.day);
            }
        }
    }
}

void delete_from_bst(BSTNode **root)
{
    if ((*root)->left == NULL && (*root)->right == NULL)
    {
        free(*root);
        *root = NULL;
        puts("");
    }
    else if ((*root)->left != NULL && (*root)->right != NULL)
    {
        BSTNode **tmp = max_bst((*root)->left);
        (*root)->list = (*tmp)->list;
        delete_from_bst(tmp);
    }
    else
    {
        BSTNode *tmp = (*root)->left ? (*root)->left : (*root)->right;
        free(*root);
        *root = tmp;
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

void delete(BSTNode **root, int dept, int id)
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
            delete (&((*root)->left), tmp->list->costumer.dept, tmp->list->costumer.id);
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
        if ((*root)->list->costumer.dept > dept)
        {
            delete (&((*root)->left), dept, id);
        }
        else
        {
            delete (&((*root)->right), dept, id);
        }
    }
}

void print()
{
    tree_in_order(sort_by_dept_root, print_costumer);
}