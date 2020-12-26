#ifndef __LIST_H__
#define __LIST_H__

#define STR_LEN                 10u

#define FOREACH(__list, __i)\
    for (node_t *__i = __list->head; __i != NULL; __i = __i->next)

struct node_s
{
    char str[STR_LEN + 1u];
    struct node_s *next;
};

typedef struct node_s node_t;

struct list_s
{
    node_t *head;
    node_t *tail;
};

typedef struct list_s list_t;

list_t *init_list(void);
void clean_list(list_t *list);
int list_pushback(list_t *list, void *str);

#endif // __LIST_H__
