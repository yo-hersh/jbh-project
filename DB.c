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
    Dept dept;
    struct _List *next;
} List;

// a binary tree
// using to get indexes
// wee creating a tree to index the dept sum and the id
typedef struct _BSTNode
{
    List *list;
    struct _BSTNode *right, *left;
} BSTNode;

List *head = NULL, *tail = NULL;
BSTNode *sort_by_id_root = NULL;
BSTNode *sort_by_dept_root = NULL;

void tree_in_order(BSTNode *root);
void add_new(Dept *new);
void add_to_id_BST(BSTNode **root, List *list);
void add_to_dept_BST(BSTNode **root, List *list);
void add_dept_in_tail(Dept *dept);
List *find_by_id(BSTNode *root, int id);

void create_list(FILE *file)
{
    char buf[100];
    while (fgets(buf, sizeof(buf), file))
    {
        Dept *new = create_dept_from_str(buf);
        add_new(new);
    }
    tree_in_order(sort_by_dept_root);
};

void add_dept_in_tail(Dept *dept)
{
    List *new = calloc(1, sizeof(List));
    new->dept = (*dept);
    
    if (tail)
    {
        (tail)->next = new;
    }
    (tail) = new;
    free(dept);

    // its hear for an option to create the first costumer from the shall, not from file.
    if (!head)
    {
        head = tail;
    }
}

void add_new(Dept *new)
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
        // if name is not equal throw error
        // else
        found->dept.dept += new->dept;
        strcpy(found->dept.date, new->date);

        free(new);
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

    if ((*id_root)->list->dept.id > list->dept.id)
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

    if ((*dept_root)->list->dept.dept <= list->dept.dept)
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
    // tree_in_order(root->right);
    // creat a task to do
    // or a void func to do everything
    printf("%s %s, dept: %d\n", root->list->dept.first_name, root->list->dept.last_name, root->list->dept.dept);
    tree_in_order(root->right);
    // tree_in_order(root->left);
}

List *find_by_id(BSTNode *root, int id)
{
    if (!root)
    {
        return NULL;
    }

    if (root->list->dept.id == id)
    {
        return root->list;
    }

    if (id > root->list->dept.id)
    {
        return find_by_id(root->right, id);
    }
    else
    {
        return find_by_id(root->left, id);
    }
}