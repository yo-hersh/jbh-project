#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "DB.h"
#include "str_handle.h"

// לבדוק שההקצאה הצליחה

typedef enum
{
    ID,
    DEPT
} SORT_BY_E;

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

void tree_in_order(BSTNode *root);
void add_new(Costumer *new);
void add_to_id_BST(BSTNode **root, List *list);
void add_to_dept_BST(BSTNode **root, List *list);
void add_dept_in_tail(Costumer *costumer);
List *find_by_id(BSTNode *root, int id);
void compare(Costumer *costumer, void *arr, int *arr_length, OPER_E oper);
void compere_with_tree(Costumer *costumer, void *arr, BSTNode *root, int *arr_length, OPER_E oper);


void create_list(FILE *file)
{
    char buf[100];
    while (fgets(buf, sizeof(buf), file))
    {
        Costumer *new = create_dept_from_str(buf);
        add_new(new);
    }
};

void add_new(Costumer *new)
{
    List *found = NULL;
    found = find_by_id(sort_by_id_root, new->id);

    if (found == NULL)
    {
        add_dept_in_tail(new);
        add_to_id_BST(&sort_by_id_root, tail);
        add_to_dept_BST(&sort_by_dept_root, tail);
    }
    else
    {
        if (found->first_name != new->first_name)
        {
            printf("first name is not equal to the name in the DB");
            goto free;
        }

        if (found->last_name != new->last_name)
        {
            printf("last name is not equal to the name in the DB");
            goto free;
        }

        found->costumer.dept += new->dept;
        found->costumer->phone = new->costumer->phone;
        strcpy(found->costumer.date, new->date);
    free:
        free(new);
    }
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

    // its hear for an option to create the first costumer from the shall, not from file.
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

    if ((*dept_root)->list->costumer.dept <= list->costumer.dept)
    {
        add_to_dept_BST(&((*dept_root)->left), list);
    }
    else
    {
        add_to_dept_BST(&((*dept_root)->right), list);
    }
}

void tree_in_order(BSTNode *root)
{
    if (!root)
    {
        return;
    }

    tree_in_order(root->left);
    printf("%s %s, costumer: %d\n", root->list->costumer.first_name, root->list->costumer.last_name, root->list->costumer.dept);
    tree_in_order(root->right);
}

List *find_by_id(BSTNode *root, int id)
{
    if (!root)
    {
        return NULL;
    }

    if (root->list->costumer.id == id)
    {
        return root->list;
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

// need to change to void func
void compare(Costumer *costumer, void *arr, int *arr_length, OPER_E oper)
{
    compere(costumer, arr, sort_by_dept_root, arr_length, oper);
}

void compere_with_tree(Costumer *costumer, void *arr, BSTNode *root, int *arr_length, OPER_E oper)
{
    if (!root)
    {
        return;
    }
    tree_in_order(root->left);
    int ret = func_to_comp(root, costumer);
    switch (oper)
    {
    case GREETER:
        if (ret > 0)
        {
            add_to_arr(arr, root, arr_length);
        }
        break;
    case SMALLER:
        if (ret < 0)
        {
            add_to_arr(arr, root, arr_length);
        }
        break;
    case EQUAL:
        if (ret == 0)
        {
            add_to_arr(arr, root, arr_length);
        }
        break;
    case NOT_EQUAL:
        if (ret != 0)
        {
            add_to_arr(arr, root, arr_length);
        }
        break;
    }
    tree_in_order(root->right);
}

void add_to_arr(void *arr, BSTNode *root, int *arr_length)
{
    arr_length++;
    arr = realloc(arr, arr_length * sizeof(void *));
    arr[arr_length - 1] = &root->costumer;
}

void *func_to_comp(BSTNode *root, Costumer *costumer)
{
    // צריך לטפל באורך ההשוואה , במידה והlist קטן יותר יחזיר true

    if (costumer->first_name)
    {
        return memcmp(root->list->first_name, costumer->first_name, strlen(root->list->first_name));
    }
    else if (costumer->last_name)
    {
        return memcmp(root->list->last_name, costumer->last_name, strlen(root->list->last_name));
    }
    else if (costumer->id)
    {
        return memcmp(root->list->id, costumer->id, strlen(root->list->id));
    }
    else if (costumer->phone)
    {
        return memcmp(root->list->phone, costumer->phone, strlen(root->list->phone));
    }
    else if (costumer->dept)
    {
        return memcmp(root->list->dept, costumer->dept, strlen(root->list->dept));
    }
    else if (costumer->date)
    {
        int year = memcmp(root->list->date->year, costumer->data->year, sizeof(int));
        if (year)
        {
            return year;
        }
        else
        {
            int mount = memcmp(root->list->date->mount, costumer->data->mount, sizeof(int));
            if (mount)
            {
                return mount;
            }
            else
            {
                return memcmp(root->list->date->day, costumer->data->day, sizeof(int));
            }
        }
    }
}