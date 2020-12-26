#include <stdio.h>
#include "funcs.h"
#include "myerror.h"
#include "vector.h"

int main(const int argc, const char **argv) 
{
    parsed_args_t pa;

    int res = parse_args(argc, argv, &pa);

    if (res)
        return res;

    vector_t *vec = init_vector();

    if (vec == NULL)
        return ALLOCATION_FAULT;

    if (read_file(pa.f, vec, pa.field))
    {
        clean_vector(vec);
        return BAD_FILE;
    }
    
    if (!vec->len)
    {
        clean_vector(vec);
        return EMPTY_FILE;
    }

    if (argc == 4)
        res = myfind(KEY, vec, pa.cmp_func, pa.field);
    else
        print_vec(vec);
    
    clean_vector(vec);

    return res || (fclose(pa.f) == EOF);
}
