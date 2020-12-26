#include <math.h>
#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include "libarr.h"

#define PRECISION       1e-6

EXPORT
int arr_lshift(int *arr, int len, int k)
{
    if (k < 0 || len <= 0 || arr == NULL)
        return -1;
    

    for (int i = 0; i < k; i++)
    {
        int j;
        int first = arr[0];

        for (j = 0; j < len - 1; j++)
            arr[j] = arr[j + 1];

        arr[j] = first;
    }

    return 0;
}

static bool is_sqr(int val)
{
    double sqrt_val = sqrt(val);
    

    return fabs((int) sqrt_val - sqrt_val) <= PRECISION;
}

EXPORT
int arr_nonsqr(int *arr, int len, int *new, int new_len)
{
    if (arr == NULL || len <= 0)
    {
        return -1;
    }

    int required = 0;

    if (new_len <= 0) // first call is to define new array len.
    {
        for (int i = 0; i < len; i++)
            required += !is_sqr(arr[i]);
    }
    else
    {
        if (new == NULL)
            return -1;

        for (int i = 0; i < len; i++)
        {
            if (required >= new_len)
                return -1;
            
            if (!is_sqr(arr[i]))
                new[required++] = arr[i];
        }
        
    }

    return required;
}

