#ifndef __FUNCS_H__
#define __FUNCS_H__

#include <stdio.h>
#include <stdlib.h>
#include "list.h"

int read_from_file(FILE *f, list_t *list);
int write_to_file(FILE *f, list_t *list);

list_t *reverse_list(list_t *list);

#endif // __FUNCS_H__
