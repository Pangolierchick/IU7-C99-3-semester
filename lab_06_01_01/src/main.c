#include <stdio.h>
#include "funcs.h"
#include "error.h"
#include "static_vector.h"

int main(const int argc, const char **argv) 
{
    parsed_args_t pa;

    int res = parse_args(argc, argv, &pa);

    if (res)
        return res;

    static_vector_t vec;
    init_vector(&vec);

    if (read_file(pa.f, &vec, pa.field))
        return BAD_FILE;
    
    if (!vec.len)
        return EMPTY_FILE;

    if (argc == 4)
        res = myfind(KEY, vec, pa.cmp_func, pa.field);
    else
        print_vec(vec);

    return res || (fclose(pa.f) == EOF);
}
