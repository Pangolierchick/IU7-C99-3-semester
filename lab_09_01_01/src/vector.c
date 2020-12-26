#include <stdio.h>
#include <stdlib.h>
#include "vector.h"
#include "logger.h"

vec_error_t vec_errno;

#define CHECK_INDEX(ind, vec)            \
    if (ind < 0 || ind >= vec->len)      \
    {                                    \
        vec_errno = INDEX_OUT_OF_BOUNDS; \
        return INDEX_OUT_OF_BOUNDS;      \
    }

#define EXPAND_VEC(vec)                                                              \
    if (vec->len + 1 >= vec->alloc_len)                                              \
    {                                                                                \
        vec->alloc_len *= 2;                                                         \
        vec->vec = realloc(vec->vec, vec->alloc_len * sizeof(vector_type));          \
        if (vec->vec == NULL)                                                        \
            return ALLOCATION_FAULT;                                                 \
        DBG_PRINT("Vector %p realloced %d\n", GENERIC_POINTER(vec), vec->alloc_len); \
    }

static void left_shift(vector_t *vec, int ind)
{
    for (int i = ind + 1; i < vec->len; i++)
        vec->vec[i - 1] = vec->vec[i];
}

static void right_shift(vector_t *vec, int ind)
{
    DBG_PRINT("Vec: len %d, alloced %d, ind %d\n", vec->len, vec->alloc_len, ind);
    int i = vec->len - ind;
    int start = vec->len;
    while (i--)
    {
        vec->vec[start] = vec->vec[start - 1];
        start--;
    }
}

vec_error_t pop(vector_t *vec, const int ind, vector_type *dst)
{
    CHECK_INDEX(ind, vec);

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
        vec->len--;
    }

    return NO_ERROR;
}

vec_error_t insert(vector_t *vec, const vector_type *val, const int ind)
{
    if (ind < 0 || ind > vec->len)
    {
        vec_errno = INDEX_OUT_OF_BOUNDS;
        return INDEX_OUT_OF_BOUNDS;
    }

    EXPAND_VEC(vec);

    if (ind == vec->len)
    {
        vec->vec[vec->len++] = *val;
    }
    else
    {
        right_shift(vec, ind);
        vec->vec[ind] = *val;
        vec->len++;
    }

    return vec_errno;
}

vec_error_t append(vector_t *vec, const vector_type *val)
{
    return insert(vec, val, vec->len);
}

vec_error_t get(const vector_t *vec, const int ind, vector_type *dst)
{
    CHECK_INDEX(ind, vec);

    *dst = vec->vec[ind];

    return NO_ERROR;
}

vec_error_t set(vector_t *vec, const int ind, const vector_type *src)
{
    CHECK_INDEX(ind, vec);

    vec->vec[ind] = *src;

    return NO_ERROR;
}

vector_t *init_vector(void)
{
    DBG_PUT("Initializing vector\t.........\t");

    vector_t *vec = malloc(sizeof(vector_t));

    if (vec == NULL)
    {
        vec_errno = ALLOCATION_FAULT;
        DBG_PUTS("Failed");
        return NULL;
    }

    vec->alloc_len = INIT_SIZE;
    vec->len = 0;

    vec->vec = calloc(INIT_SIZE, sizeof(vector_type));

    if (vec->vec == NULL)
    {
        clean_vector(vec);
        vec_errno = ALLOCATION_FAULT;
        DBG_PUTS("Failed");
        return NULL;
    }


    DBG_PRINT("%p\n", GENERIC_POINTER(vec));

    return vec;
}

void clean_vector(vector_t *vec)
{
    DBG_PRINT("Cleaning vector\t%p\n", GENERIC_POINTER(vec));
    
    if (vec != NULL)
    {
        for (int i = 0; i < vec->len; i++)
        {
            DBG_PRINT("name: %p\n", GENERIC_POINTER(vec->vec[i].name));
            DBG_PRINT("title: %p\n", GENERIC_POINTER(vec->vec[i].title));
                
            
            if (vec->vec[i].name != NULL)
                free(vec->vec[i].name);
            
            if (vec->vec[i].title != NULL)
                free(vec->vec[i].title);
        }

        DBG_PRINT("Array:\t%p\n", GENERIC_POINTER(vec->vec));
        free(vec->vec);
        free(vec);
    }
}

vector_type *init_vector_type(void)
{
    vector_type *elem = malloc(sizeof(vector_type));

    if (elem == NULL)
        return NULL;

    elem->name = NULL;

    elem->title = NULL;

    return elem;
}

void clean_vector_type(vector_type *elem)
{
    if (elem)
    {
        if (elem->name)
            free(elem->name);
        
        if (elem->title)
            free(elem->title);
        
        free(elem);
    }
}
