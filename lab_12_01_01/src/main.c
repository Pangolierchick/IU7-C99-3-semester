#include <stdio.h>
#include <stdlib.h>
#include "arraylib.h"
#include "filelib.h"
#include "palib.h"
#include "macrologger.h"

#define FUNC_TESTS          1

#ifdef FUNC_TESTS
#pragma message "Prints for func tests is on"
#endif

int int_cmp(const void *a, const void *b)
{
    int val_a = *((int *) a);
    int val_b = *((int *) b);

    return val_a - val_b;
}

int main(int argc, char **argv)
{
    pa_args_t pa_args;

    int res = parse_args(argc, argv, &pa_args);

    LOG_DEBUG("res after parse %d", res);
    if (res)
    {
        return res;
    }
    
    int *pa = NULL;
    int *pb = NULL;

    res = read_file(pa_args.fi, &pa, &pb);

    if (res)
    {
        LOG_DEBUG("res after read %d", res); 
        free(pa);
        return res;
    }

    if (pa_args.filter)
    {
        int *new_pa = NULL;
        int *new_pb = NULL;

        res = key(pa, pb, &new_pa, &new_pb);

        if (res)
        {
            free(pa);
            return res;
        }
        
        free(pa);

        pa = NULL;
        pb = NULL;
        
        mysort(new_pa, new_pb - new_pa, sizeof(int), int_cmp);
#if LOG_LEVEL > NO_LOGS || defined FUNC_TESTS
        print_arr(new_pa, new_pb);
#endif
        write_file(pa_args.fo, new_pa, new_pb);

        free(new_pa);
        new_pa = NULL;
        new_pb = NULL;
    }
    else
    {
        mysort(pa, pb - pa, sizeof(int), int_cmp);
#if LOG_LEVEL > NO_LOGS || defined FUNC_TESTS
        print_arr(pa, pb);
#endif
        write_file(pa_args.fo, pa, pb);
    }

    free(pa);
    pa = NULL;
    pb = NULL;

    return fclose(pa_args.fi) == EOF || fclose(pa_args.fo) == EOF;
}
