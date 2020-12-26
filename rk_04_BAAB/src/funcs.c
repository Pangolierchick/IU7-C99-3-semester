#include "funcs.h"

int read_from_file(FILE *f, list_t *list)
{
    int rc = 1;
    char str[STR_LEN + 1u];

    while (rc == 1)
    {
        rc = fscanf(f, "%11s", str);

        if (rc == 1)
        {
            if (list_pushback(list, (void *) str) == -1)
            {
                clean_list(list);
                return -1;
            }
        }
    }

    return rc != EOF;
}

int write_to_file(FILE *f, list_t *list)
{
    FOREACH(list, i)
    {
        fprintf(f, "%s ", i->str);
    }

    fprintf(f, "\n");

    return 0;
}

list_t *reverse_list(list_t *list)
{
    node_t *i = list->head->next;

    node_t *tail = list->head;
    node_t *head = tail;
    node_t *new_head = list->tail;

    while (i)
    {
        node_t *tmp = i->next;
        i->next = head;
        head = i;
        i = tmp;
    }

    list->tail = tail;
    list->tail->next = NULL;
    list->head = new_head;

    return list;
}
