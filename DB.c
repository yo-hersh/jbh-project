#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "DB.h"
#include "str_handling.h"

// This program creates a linked list named "list" which contains "customer" structs.
// Each customer struct is added to the tail of the list and the list remains unchanged throughout the program.
// The program has two Binary Search Trees (BSTs) for fast searching;
// an "id BST" for searching by ID and a "debt BST" for indexing by debt for printing in deposed order in logarithmic time.
// The program reads a CSV file and creates a customer struct from each line.
// If the input is valid, a reference to the new customer is returned, otherwise, null is returned.
// The new customer is added to the tail of the list and both BSTs.
// If the customer ID already exists, the program checks if the name is the same,
// deletes the customer from the debt BST, updates the debt, phone, and date if needed,
// adds the customer to the debt BST and frees the memory.
// The program also allows users to add, search, and print customers.
// The program compares a new customer with all customers by traversing the debt BST,
// and uses the print function to print the result by debt BST.

typedef struct Validation
{
    int (*valid_func)(char *value);
    int (*add_func)(Customer *customer, char *value);
    const char *error_msg;
} Validation;

Validation validations[] = {
    {valid_name, add_f_name, "first name required to be letters only, at least 2\n"},
    {valid_name, add_s_name, "second name required to be letters only, at least 2\n"},
    {valid_id, add_id, "id required to be 9 digits only\n"},
    {valid_phone, add_phone, "phone required to be 10 digits only, start by 0\n"},
    {valid_date, add_date, "date required to be in dd/mm/yyyy format between 1970-2100\n"},
    {valid_debt, add_debt, "debt required to be digits only\n"},
};

typedef struct _List
{
    Customer customer;
    struct _List *next;
} List;

typedef struct _BSTNode
{
    List *list;
    struct _BSTNode *right, *left;
} BSTNode;

static List *head = NULL, *tail = NULL;
static BSTNode *sort_by_id_root = NULL;
static BSTNode *sort_by_debt_root = NULL;

int add_new(Customer *new, PRINT_HANDLING print, int print_to, unsigned int line);
int create_customer(char *str, unsigned int line, PRINT_HANDLING print, int print_to);
void add_to_debt_BST(BSTNode **root, List *list);
void add_to_id_BST(BSTNode **root, List *list);
void add_debt_in_tail(Customer *customer);
void compare_str(char *str, char *oper, unsigned int index, PRINT_HANDLING print, int print_to);
int comp_values(Customer *root, Customer *customer);
int comp_date(Customer *customer_1, Customer *customer_2);
void comp_in_tree(BSTNode *root, Customer *customer, char *oper, PRINT_HANDLING print, int print_to);
void tree_in_order(BSTNode *root, void (*do_something)(Customer *customer, void *func, void *arg), void *func, void *arg);
void delete_debt_bst(BSTNode **root, int debt, unsigned int id);
void free_all();
void free_tree(BSTNode *root);
void free_list(List *head);
BSTNode *max_bst(BSTNode *root);
Customer *create_customer_from_str(char *str, unsigned int line, PRINT_HANDLING print, int print_to);
Customer *create_comp_customer(char *str, unsigned int index, PRINT_HANDLING print, int print_to);
BSTNode *find_by_id(BSTNode *root, unsigned int id);

void create_list(FILE *file)
{
    char buf[BUF_LEN];
    unsigned int line = 0;
    while (fgets(buf, BUF_LEN, file))
    {
        if (buf_overflow(buf, print_to_stdout, 0))
        {
            continue;
        }

        create_customer(buf, ++line, print_to_stdout, 0);
    }
    fclose(file);
    print_all(print_to_stdout, 0);
}

int create_customer(char *str, unsigned int line, PRINT_HANDLING print, int print_to)
{
    Customer *new = create_customer_from_str(str, line, print, print_to);
    if (new)
    {
        return add_new(new, print, print_to, line);
    }
    return 1;
}

Customer *create_customer_from_str(char *str, unsigned int line, PRINT_HANDLING print, int print_to)
{
    Customer *new = calloc(1, sizeof(Customer));
    if (!new)
    {
        perror("error creating new debt");
        return NULL;
    }

    char *value;
    unsigned int error_code = 0;
    char line_str[30] = {0};
    if (line)
    {
        sprintf(&(line_str[0]), "error line %d: ", line);
    }

    str_to_lower(str);
    remove_white_spaces(str);
    value = strtok(str, ",");

    for (int i = 0; i < SIZEOF_VALUES; i++)
    {
        remove_white_spaces(value);
        if (validations[i].valid_func(value))
        {
            if (!(validations[i].add_func(new, value)))
            {
                goto error;
            }
        }
        else
        {
            error_code |= 1 << i;
        }
        value = strtok(NULL, ",");
    }

    if (error_code || value)
    {
        for (int i = 0; i < ARR_LEN(validations); i++)
        {
            if (error_code & 1 << i)
            {
                print(print_to, line_str);
                print(print_to, validations[i].error_msg);
            }
        }
        if (value)
        {
            print(print_to, line_str);
            print(print_to, "too many values\n");
        }
        goto error;
    }

    return new;
error:
    free(new->first_name);
    free(new->second_name);
    free(new);
    return NULL;
}

int add_new(Customer *new, PRINT_HANDLING print, int print_to, unsigned int line)
{
    int ret = 0;
    // check is the id is already exits
    BSTNode *found = find_by_id(sort_by_id_root, new->id);

    if (!found)
    {
        add_debt_in_tail(new);
        add_to_id_BST(&sort_by_id_root, tail);
        add_to_debt_BST(&sort_by_debt_root, tail);
    }
    else
    {
        char line_str[30] = {0};
        if (line)
        {
            sprintf(&(line_str[0]), "error line %d: ", line);
        }
        if (strcmp(found->list->customer.first_name, new->first_name))
        {
            print(print_to, line_str);
            print(print_to, "the first name is not equal to the name in the DB\n");
            ret = 1;
            goto free;
        }

        if (strcmp(found->list->customer.second_name, new->second_name))
        {
            print(print_to, line_str);
            print(print_to, "the second name is not equal to the name in the DB\n");
            ret = 1;
            goto free;
        }

        List *list = found->list;
        delete_debt_bst(&sort_by_debt_root, list->customer.debt, list->customer.id);
        list->customer.debt += new->debt;
        list->customer.phone = new->phone;
        if (comp_date(&(list->customer), new) < 0)
        {
            list->customer.date = new->date;
        }

        add_to_debt_BST(&sort_by_debt_root, list);
    free:
        free(new->first_name);
        free(new->second_name);
        free(new);
    }
    return ret;
}

void add_debt_in_tail(Customer *customer)
{
    List *new = calloc(1, sizeof(List));
    if (!new)
    {
        perror("error creating new list");
        return;
    }

    new->customer = (*customer);

    if (tail)
    {
        (tail)->next = new;
    }
    (tail) = new;
    free(customer);

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

    if (list->customer.id <= (*id_root)->list->customer.id)
    {
        add_to_id_BST(&((*id_root)->left), list);
    }
    else
    {
        add_to_id_BST(&((*id_root)->right), list);
    }
}

void add_to_debt_BST(BSTNode **debt_root, List *list)
{
    if (*debt_root == NULL)
    {
        *debt_root = calloc(1, sizeof(BSTNode));
        if (!debt_root)
        {
            perror("error creating new debt_bst");
            return;
        }

        (*debt_root)->list = list;
        return;
    }

    if (list->customer.debt <= (*debt_root)->list->customer.debt)
    {
        add_to_debt_BST(&((*debt_root)->left), list);
    }
    else
    {
        add_to_debt_BST(&((*debt_root)->right), list);
    }
}

void tree_in_order(BSTNode *root, void (*do_something)(Customer *customer, void *func, void *arg), void *func, void *arg)
{
    if (!root)
    {
        return;
    }

    tree_in_order(root->left, do_something, func, arg);
    do_something(&(root->list->customer), func, arg);
    tree_in_order(root->right, do_something, func, arg);
}

BSTNode *find_by_id(BSTNode *root, unsigned int id)
{
    if (!root)
    {
        return NULL;
    }

    if (root->list->customer.id == id)
    {
        return root;
    }

    if (id > root->list->customer.id)
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
    Customer *new = create_comp_customer(str, index, print, print_to);
    if (new)
    {
        comp_in_tree(sort_by_debt_root, new, oper, print, print_to);
        free(new);
    }
}

Customer *create_comp_customer(char *str, unsigned int index, PRINT_HANDLING print, int print_to)
{
    Customer *new = calloc(1, sizeof(Customer));
    if (!new)
    {
        perror("error creating new debt to comp");
        return NULL;
    }

    if (validations[index].valid_func(str))
    {
        if (!validations[index].add_func(new, str))
        {
            goto error;
        }
        else
        {
            return new;
        }
    }
    print(print_to, validations[index].error_msg);
error:
    return NULL;
}

void comp_in_tree(BSTNode *root, Customer *customer, char *oper, PRINT_HANDLING print, int print_to)
{
    if (!root)
    {
        return;
    }

    comp_in_tree(root->left, customer, oper, print, print_to);
    int ret = comp_values(&(root->list->customer), customer);
    if (strstr(oper, ">"))
    {
        if (ret > 0)
        {
            print_customer(&(root->list->customer), print, print_to);
        }
    }
    else if (strstr(oper, "<"))
    {
        if (ret < 0)
        {
            print_customer(&(root->list->customer), print, print_to);
        }
    }
    else if (strstr(oper, "!="))
    {
        if (ret != 0)
        {
            print_customer(&(root->list->customer), print, print_to);
        }
    }
    else if (strstr(oper, "="))
    {
        if (ret == 0)
        {
            print_customer(&(root->list->customer), print, print_to);
        }
    }

    comp_in_tree(root->right, customer, oper, print, print_to);
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

int comp_values(Customer *root, Customer *comp)
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
    else if (comp->debt)
    {
        return comp_int(root->debt, comp->debt);
    }
    else if (comp->date.year)
    {
        return comp_date(root, comp);
    }
    return 1;
}

int comp_date(Customer *customer_1, Customer *customer_2)
{
    int year = comp_int(customer_1->date.year, customer_2->date.year);
    if (year)
    {
        return year;
    }
    else
    {
        int month = comp_int(customer_1->date.month, customer_2->date.month);
        if (month)
        {
            return month;
        }
        else
        {
            return comp_int(customer_1->date.day, customer_2->date.day);
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

void delete_debt_bst(BSTNode **root, int debt, unsigned int id)
{
    if (*root == NULL)
    {
        return;
    }

    if ((*root)->list->customer.id == id && (*root)->list->customer.debt == debt)
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
            delete_debt_bst(&((*root)->left), tmp->list->customer.debt, tmp->list->customer.id);
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
        if (debt <= (*root)->list->customer.debt)
        {
            delete_debt_bst(&((*root)->left), debt, id);
        }
        else
        {
            delete_debt_bst(&((*root)->right), debt, id);
        }
    }
}

void print_all(PRINT_HANDLING print, int print_to)
{
    tree_in_order(sort_by_debt_root, (void *)print_customer, (void *)print, (void *)print_to);
}

void free_all()
{
    free_tree(sort_by_debt_root);
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
        free(head->customer.first_name);
        free(head->customer.second_name);
        free(head);
        head = temp;
    }
}