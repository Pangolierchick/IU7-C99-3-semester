#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "list.h"


list_t *init_list(void)
{
    list_t *list = calloc(1, sizeof(list_t));

    return list;
}

static node_t *init_node(char *val)
{
    node_t *node = malloc(sizeof(node_t));

    if (node)
    {
        strcpy(node->str, val);
        node->next = NULL;
    }

    return node;
}

void clean_list(list_t *list)
{
    if (list)
    {
        node_t *i = list->head;

        while (i)
        {
            node_t *tmp = i->next;

            free(i);
            i = tmp;
        }

        free(list);
    }
}

int list_pushback(list_t *list, void *str)
{
    node_t *new_node = init_node(str);

    if (new_node == NULL)
        return -1;

    if (list->head == NULL && list->tail == NULL)
    {
        list->head = new_node;
        list->head->next = list->tail;

        list->tail = new_node;
    }
    else if (list->head && list->tail)
    {
        list->tail->next = new_node;
        list->tail = list->tail->next;
    }
    else
        return -1;

    return 0;
}
