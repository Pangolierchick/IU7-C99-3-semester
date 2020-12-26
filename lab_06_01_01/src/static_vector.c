#include <stdio.h>
#include "static_vector.h"

vec_error_t vec_errno;

#define CHECK_INDEX()                    \
    if (ind < 0 || ind >= vec->len)      \
    {                                    \
        vec_errno = INDEX_OUT_OF_BOUNDS; \
        return INDEX_OUT_OF_BOUNDS;      \
    }

static void left_shift(static_vector_t *vec, int ind)
{
    for (int i = ind + 1; i < vec->len; i++)
        vec->vec[i - 1] = vec->vec[i];
    vec->len--;
}

static void right_shift(static_vector_t *vec, int ind)
{
    int i = vec->len - ind;
    int start = vec->len;
    while (i--)
    {
        vec->vec[start] = vec->vec[start - 1];
        start--;
    }

    vec->len++;
}

vec_error_t pop(static_vector_t *vec, const int ind, vector_type *dst)
{
    CHECK_INDEX();

    if (!vec->len)
    {
        vec_errno = VECTOR_UNDERFLOW;
        return VECTOR_UNDERFLOW;
    }

    if (ind == vec->len - 1)
    {
        *dst = vec->vec[--vec->len];
    }
    else
    { 
        *dst = vec->vec[ind];
        left_shift(vec, vec->len - ind);
    }

    return NO_ERROR;
}

vec_error_t insert(static_vector_t *vec, const vector_type val, const int ind)
{
    if (ind < 0 || ind > vec->len)
    {
        vec_errno = INDEX_OUT_OF_BOUNDS;
        return INDEX_OUT_OF_BOUNDS;
    }

    if (vec->len >= STATIC_VECTOR_SIZE)
    {
        vec_errno = VECTOR_OVERFLOW;
        return VECTOR_OVERFLOW;
    }

    if (ind == vec->len)
    {
        vec_errno = append(vec, val);
    }
    else
    {
        right_shift(vec, ind);
        vec->vec[ind] = val;
    }

    return vec_errno;
}

vec_error_t append(static_vector_t *vec, const vector_type val)
{
    if (vec->len >= STATIC_VECTOR_SIZE)
    {
        vec_errno = VECTOR_OVERFLOW;
        return VECTOR_OVERFLOW;
    }

    vec->vec[vec->len++] = val;
    return NO_ERROR;
}

vec_error_t get(const static_vector_t *vec, const int ind, vector_type *dst)
{
    CHECK_INDEX();

    *dst = vec->vec[ind];

    return NO_ERROR;
}

vec_error_t set(static_vector_t *vec, const int ind, const vector_type src)
{
    CHECK_INDEX();

    vec->vec[ind] = src;

    return NO_ERROR;
}

void init_vector(static_vector_t *vec)
{
    vec->len = 0;
}


