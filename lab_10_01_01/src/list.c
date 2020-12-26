#include <stdlib.h>
#include <assert.h>
#include "list.h"
#include "my_error.h"
#include "logger.h"


#define LESS_THAN(a, b) \
    (cmp(a->data, b->data) < 0)

node_t *init_node(void *data)
{
    node_t *node = calloc(1, sizeof(node_t));

    if (node == NULL)
        return NULL;

    node->data = data;

    return node;
}

void clear_list(node_t **list)
{
    if (*list)
    {
        node_t *curr_node = *list;

        while (curr_node != NULL)
        {
            node_t *next = curr_node->next;
            free(curr_node);
            curr_node = next;
        }

        *list = NULL;
    }
}

void full_clear_list(node_t **list)
{
    if (*list)
    {
        node_t *curr_node = *list;

        while (curr_node != NULL)
        {
            node_t *next = curr_node->next;
            DBG_PRINT("data %p\t%p\n", (void *) curr_node, curr_node->data);
            free(curr_node->data);
            free(curr_node);
            curr_node = next;
        }

        *list = NULL;
    }
}

int pushback(node_t **list, void *data)
{
    if (data == NULL)
        return EXIT_FAILURE;
    
    if (list == NULL)
        return EXIT_FAILURE;

    node_t *new = init_node(data);

    if (new == NULL)
        return ALLOC_ERROR;

    if (*list == NULL)
    {
        DBG_PUTS("Zero len list");
        *list = new;
        return NO_ERROR;
    }

    node_t *curr;
    // mne tak ne nravitsya :-)
    for (curr = *list; curr->next; curr = curr->next);

    curr->next = new;

    return NO_ERROR;
}

void print_list(const node_t *list, print_func pf)
{
    const node_t *curr = list;

    printf("List:\n");

    while (curr != NULL)
    {
        pf(curr->data);
        curr = curr->next;
    }

    printf("\n");
}

node_t *find(node_t *head, const void *data, cmp_func cmp)
{
    if (data == NULL)
        return NULL;
    
    if (cmp == NULL)
        return NULL;

    node_t *curr = head;

    while (curr != NULL)
    {
        if (cmp(data, curr->data) == 0)
            return curr;

        curr = curr->next;
    }

    return NULL;
}

void insert(node_t **head, node_t *elem, node_t *before)
{
    if (head == NULL)
        return;
    
    if (elem == NULL)
        return;
    
    if (before == NULL)
        return;
    
    if (*head == NULL)
        return;

    if (*head == before)
    {
        elem->next = before;
        *head = elem;
    }
    else
    {
        // 1 -> 2 -> 4 -> 5
        //         ^
        //         |
        //         3
        //
        // 1 -> 2 -> 3 -> 4 -> 5


        node_t *curr = *head;
        while (curr->next)
        {
            if (curr->next == before)
            {
                curr->next = elem;
                elem->next = before;
                return;
            }

            curr = curr->next;
        }
    }
}

void remove_duplicates(node_t **head, cmp_func cmp)
{
    if (head == NULL)
        return;
    
    if (*head == NULL)
        return;

    if (cmp == NULL)
        return;

    node_t *new = init_node((*head)->data);

    if (new == NULL)
        return;

    node_t *curr = (*head)->next;

    while (curr)
    {
        if (find(new, curr->data, cmp) == NULL)
        {
            // printf("curr data: %d\n", *((int *)curr->data));
            if (pushback(&new, curr->data))
            {
                clear_list(&new);
                return;
            }
        }
        curr = curr->next;
    }

    clear_list(head);
    *head = new;
}

// 1 2 4 3
// 1 2 0 3
// 

node_t *sort(node_t *head, cmp_func cmp)
{
    if (head == NULL)
        return NULL;
    
    if (cmp == NULL)
        return NULL;


    node_t *new = NULL;
    node_t *curr = head;

    while (curr != NULL)
    {
        node_t *next = curr->next;
        
        DBG_PRINT("curr: %d\n", *((int *)curr->data));
        sorted_insert(&new, curr, cmp);
        
        curr = next;
    }

    return new;
}

void sorted_insert(node_t **head, node_t *element, cmp_func cmp)
{
    if (*head == NULL || cmp(element->data, (*head)->data) <= 0)
    {
        element->next = *head;
        *head = element;
    }
    else
    {
        //  4 3 2 1
        node_t *curr = *head;

        while (curr->next && LESS_THAN(curr->next, element))
            curr = curr->next;

        element->next = curr->next;
        curr->next = element;
    }
}

int check_sort(node_t *head, cmp_func cmp)
{
    node_t *left = head;
    node_t *right = head->next;

    while (right)
    {
        if (cmp(left->data, right->data) > 0)
            return 1;
        left = left->next;
        right = right->next;
    }

    // printf("Sorted!\n");
    return 0;
}
