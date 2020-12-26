#ifndef __LIST_H__
#define __LIST_H__

struct node_s
{
    void *data;
    struct node_s *next;
};

#define FOREACH(__list, __i) \
    for (node_t *__i = __list; __i != NULL; __i = __i->next)

typedef struct node_s node_t;

typedef void print_func(const void *src);
typedef int cmp_func(const void *, const void *);

node_t *init_node(void *data);
void clear_list(node_t **list);
void full_clear_list(node_t **list);


int pushback(node_t **list, void *data);

void print_list(const node_t *list, print_func pf);

node_t *find(node_t *head, const void *data, cmp_func cmp); // TO TEST
void insert(node_t **head, node_t *elem, node_t *before); // TO TEST

void remove_duplicates(node_t **head, cmp_func cmp); // TO TEST

node_t *sort(node_t *head, cmp_func cmp); // TO TEST
void sorted_insert(node_t **head, node_t *element, cmp_func cmp);
int check_sort(node_t *head, cmp_func cmp);

#endif // __LIST_H__
