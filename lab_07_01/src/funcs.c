#include <string.h>
#include "../inc/funcs.h"
#include "../inc/error.h"
#include "../inc/defines.h"
#include "../inc/macrologger.h"

int mysort_errno;

void array_min_max(const int *arr_b, const int *arr_e, array_elem_t *p_min, array_elem_t *p_max)
{
    array_elem_t min = {.val = *arr_b, .ind = 0 };
    array_elem_t max = {.val = *arr_b, .ind = 0 };

    const int *p_arr_b = arr_b + 1;
    int len = arr_e - arr_b - 1;
    int ind = 1;

    while (len--)
    {
        ELEM_MIN(min, *p_arr_b, ind);
        ELEM_MAX(max, *p_arr_b, ind);

        p_arr_b++;
        ind++;        
    }

    *p_min = min;
    *p_max = max;
}

void print_arr(const int *arr_b, const int *arr_e)
{
    int len = arr_e - arr_b;
    const int *parr_b = arr_b;

    for (int i = 0; i < len; i++)
        printf("%d\n", *parr_b++);
}

int int_cmp(const void *a, const void *b)
{
    int val_a = *((int *) a);
    int val_b = *((int *) b);

    return val_a - val_b;
}

int parse_args(int argc, char **argv, pa_args_t *pa)
{
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

// between max and min
int key(const int *pb_src, const int *pe_src, int **pb_dst, int **pe_dst)
{
    array_elem_t min;
    array_elem_t max;

    if (!pb_src || !pe_src || !pb_dst || !pe_dst)
        return NULL_POINTER;

    if (pe_src - pb_src <= 2)
        return EQUAL_ARRAY_FILTER_FAULT;

    array_min_max(pb_src, pe_src, &min, &max);


    LOG_DEBUG("array min = %d (%d) \tmax = %d (%d)", min.val, min.ind, max.val, max.ind);

    const int *ppb_src = pb_src;

    const int left_ind = (MIN(min.ind, max.ind)) + 1;
    const int right_ind = MAX(min.ind, max.ind);

    LOG_DEBUG("Left ind %d\tright ind %d\n", left_ind, right_ind);

    const int new_arr_len = right_ind - left_ind;
    
    LOG_DEBUG("new array len: %d", new_arr_len);

    if (new_arr_len <= 0)
        return EQUAL_ARRAY_FILTER_FAULT;

    *pb_dst = (int *) malloc(sizeof(int) * new_arr_len);

    if (*pb_dst == NULL)
        return ALLOCATION_FAULT;

    // 0         5
    // 0 1 2 3 4 5
    // 1 2 3 4 5 6
    //   | | | |
    
    int *ppb_dst = *pb_dst;
    ppb_src = pb_src + left_ind;

    for (int i = 0; i < new_arr_len; i++)
        *ppb_dst++ = *ppb_src++;

    *pe_dst = ppb_dst;
    
    return NO_ERROR;
}


void mysort(void *base, size_t __nel, size_t __width, cmp_fun cmp)
{
    if (base == NULL)
    {
        mysort_errno = NULL_BASE;
        return;
    }

    if (__nel == 0)
    {
        mysort_errno = BAD_NEL;
        return;
    }

    if (__width == 0)
    {
        mysort_errno = BAD_WIDTH;
        return;
    }

    if (cmp == NULL)
    {
        mysort_errno = NULL_CMP;
        return;
    }
    

    char *base_ptr = (char *) base;

    for (size_t i = 0; i < __nel - 1; i++)
    {
        for (size_t j = 0; j < __nel - i - 1; j++)
        {
            if (cmp((void *) (base_ptr + (__width * j)), (void *) (base_ptr + (__width * (j + 1)))) > 0)
                SWAP((base_ptr + (__width * j)), (base_ptr + (__width * (j + 1))), __width);
        }
    }
}
