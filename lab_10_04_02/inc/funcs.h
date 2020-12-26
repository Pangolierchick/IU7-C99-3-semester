#ifndef __FUNCS_H__
#define __FUNCS_H__

#include "list.h"

#define MIN(a, b) ((a) < (b) ? (a) : (b))

typedef struct factor_s
{
    int power;
    int num;
} factor_t;

int menu(void);

node_t *factorize(int val);
node_t *multiplication(node_t *left, node_t *right);
int division(const node_t *left, const node_t *right, node_t **res);
node_t *sqr(node_t *num);

void print_fact_list(node_t *src);


int out_cmd(void);
int mult_cmd(void);
int sqr_cmd(void);
int div_cmd(void);

#endif // __FUNCS_H__
