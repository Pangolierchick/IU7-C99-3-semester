#include <string.h>
#include <stdlib.h>
#include "palib.h"
#include "macrologger.h"


int parse_args(int argc, char **argv, pa_args_t *pa)
{
    if (argv == NULL || pa == NULL || *argv == NULL)
        return INCORRECT_ARGS;

    LOG_DEBUG("Argc: %d", argc);
    if (argc != 3 && argc != 4)
        return INCORRECT_ARGS;

    pa->fi = fopen(FILE_IN, "r");
    pa->fo = fopen(FILE_OUT, "w");
    pa->filter = 0;
    
    if (argc == 4)
    {
        pa->filter = !strcmp(FILTER, FILTER_KEY);
        return pa->fi == NULL || pa->fo == NULL || !pa->filter;
    }

    return pa->fi == NULL || pa->fo == NULL;
}
