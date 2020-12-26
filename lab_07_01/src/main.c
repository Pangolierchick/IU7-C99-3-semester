#include <stdio.h>
#include "../inc/error.h"
#include "../inc/funcs.h"
#include "../inc/file.h"
#include "../inc/macrologger.h"

#define FUNC_TESTS          0

#ifdef FUNC_TESTS
#pragma message "Prints for func tests if on"
#endif

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
