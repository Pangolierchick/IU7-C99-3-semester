#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
#include <stdbool.h>
#include "funcs.h"
#include "my_error.h"
#include "logger.h"
#include "defines.h"

#define INIT_FACTOR_STRUCT(this, __num, __power) \
    factor_t *this = malloc(sizeof(factor_t));   \
    if (this == NULL)                            \
        return NULL;                             \
    this->num = __num;                           \
    this->power = __power;                       \

#define FACTOR_NUM(node)            ((factor_t *) node->data)->num
#define FACTOR_POWER(node)          ((factor_t *) node->data)->power


static int num_cmp(const void *a, const void *b)
{
    const factor_t *pa = a;
    const factor_t *pb = b;

    return pb->num - pa->num;
}

static node_t *listcpy(const node_t *src)
{
    if (!src)
    {
        return NULL;
    }

    node_t *res = NULL;

    TRACE_PRINT("Copying %p\n", GENERICK_POINTER(src));

    // Doing "deep copy"
    TFOREACH(src, i, const node_t *)
    {
        INIT_FACTOR_STRUCT(tmp, FACTOR_NUM(i), FACTOR_POWER(i));

        if (pushback(&res, tmp))
        {
            free(tmp);
            full_clear_list(&res);
            return NULL;
        }
    }

    return res;
}

static inline int fact2int(node_t *src)
{
    int val = 1;

    FOREACH(src, i)
        val *= (int) pow(FACTOR_NUM(i), FACTOR_POWER(i));
    
    return val;
}

void print_fact_list(node_t *src)
{
    FOREACH(src, num)
    {
        printf("%d %d ", ((factor_t *) num->data)->num, ((factor_t *) num->data)->power);
    }

    printf("1\n");
}

int menu(void)
{
    INFO_PRINT("Print cmd: ");
    char cmd_buff[4];
    if (scanf("%3s", cmd_buff) != 1)
        return BAD_CMD;

    int res = NO_ERROR;

    if (strcmp(cmd_buff, MULTIPLICATION_CMD) == 0)
    {
        INFO_PRINT("Mul cmd inputted\n");
        res = mult_cmd();
    }
    else if (strcmp(cmd_buff, DIVISION_CMD) == 0)
    {
        INFO_PRINT("Div cmd inputted\n");
        res = div_cmd();
    }
    else if (strcmp(cmd_buff, FACTORIZE_CMD) == 0)
    {
        INFO_PRINT("Out cmd inputted\n");
        res = out_cmd();
    }
    else if (strcmp(cmd_buff, SQR_CMD) == 0)
    {
        INFO_PRINT("Sqr cmd inputted\n");
        res = sqr_cmd();
    }
    else
        res = UNKNOWN_CMD;

    return res;
}

static int factor_num_cmp(const void *a, const void *b)
{
    const factor_t *pa = a;
    const factor_t *pb = b;

    return pa->num - pb->num;
}

// 2 3 5 7
// 41

node_t *multiplication(node_t *left, node_t *right)
{
    if (left == NULL && right == NULL)
        return NULL;

    if (left == NULL && right)
        return listcpy(right);
    
    if (left && right == NULL)
        return listcpy(left);

    node_t *res = listcpy(left);

    if (res == NULL)
        return NULL;

    FOREACH(right, i)
    {
        node_t *node = find(res, i->data, factor_num_cmp);

        if (node)
            FACTOR_POWER(node) += FACTOR_POWER(i);
        else
        {
            INIT_FACTOR_STRUCT(tmp, FACTOR_NUM(i), FACTOR_POWER(i));

            if (pushback(&res, tmp))
            {
                full_clear_list(&res);
                return NULL;
            }
        }
    }

    return res;
}

node_t *factorize(int val)
{
    if (val <= 1)
        return NULL;

    node_t *num = NULL;

    int i = 2;
    int curr_pow = 0;

    while (i <= sqrt(val))
    {
        curr_pow = 0;

        TRACE_PRINT("Curr val: %d\tCurr i %d\n", val, i);

        while (val % i == 0)
        {
            TRACE_PRINT("val %d\ti %d\n", val, i);
            curr_pow++;
            val /= i;
        }

        if (curr_pow)
        {
            DBG_PRINT("Adding: %d %d\n", i, curr_pow);
            INIT_FACTOR_STRUCT(fnum, i, curr_pow);
            
            if (pushback(&num, fnum))
            {
                full_clear_list(&num);
                return NULL;
            }
        }

        if (i == 2)
            i++;
        else
            i += 2;
    }

    if (val != 1)
    {
        DBG_PRINT("Adding: %d %d\n", val, 1);
        INIT_FACTOR_STRUCT(fnum, val, 1);
            
        if (pushback(&num, fnum))
        {
            full_clear_list(&num);
            return NULL;
        }
    }

    return num;
}

node_t *sqr(node_t *num)
{
    if (num)
    {
        FOREACH(num, i)
            FACTOR_POWER(i) *= 2; 
    }

    return num;
}

int division(const node_t *left, const node_t *right, node_t **res)
{
    if (left == NULL)
        return DIVISION_ERR;
    
    if (right == NULL)
    {
        *res = listcpy(left);
        return NO_ERROR;
    }

    node_t *cleft = listcpy(left);
    node_t *cright = listcpy(right);

    if (cleft == NULL || cright == NULL)
    {
        full_clear_list(&cleft);
        full_clear_list(&cright);
        return ALLOC_ERROR;
    }

#if LOG_LEVEL >= DEBUG
    print_fact_list(cleft);
    print_fact_list(cright);
#endif

    FOREACH(cright, i)
    {
        node_t *node = find(cleft, i->data, factor_num_cmp);

        if (node)
        {
            int pow = MIN(FACTOR_POWER(node), FACTOR_POWER(i));
            FACTOR_POWER(node) -= pow;
            FACTOR_POWER(i) -= pow;

            if (FACTOR_POWER(node) == 0)
            {
                DBG_PRINT("Deliting %p\n", GENERICK_POINTER(node));
                pop(&cleft, node);
            }
        }
    }

#if LOG_LEVEL >= DEBUG
    print_fact_list(cleft);
    print_fact_list(cright);
#endif

    int left_val = fact2int(cleft);
    int right_val = fact2int(cright);

    DBG_PRINT("left: %d\tright: %d\t res: %d\n", left_val, right_val, left_val / right_val);

    if ((left_val / right_val) <= 0)
    {
        full_clear_list(&cleft);
        full_clear_list(&cright);
        return DIVISION_ERR;
    }

    *res = factorize(left_val / right_val);

    full_clear_list(&cleft);
    full_clear_list(&cright);

    return NO_ERROR;
}

int out_cmd(void)
{
    int val;

    if (scanf("%d", &val) != 1)
        return BAD_NUMBER_INPUTTED;
    
    if (val < 1)
        return BAD_NUMBER_INPUTTED;
    
    node_t *fnum = factorize(val);

    fnum = sort(fnum, num_cmp);

    print_fact_list(fnum);

    full_clear_list(&fnum);

    return NO_ERROR;
}

int mult_cmd(void)
{
    int lval;

    if (scanf("%d", &lval) != 1)
        return BAD_NUMBER_INPUTTED;
    
    if (lval < 1)
        return BAD_NUMBER_INPUTTED;

    int rval;

    if (scanf("%d", &rval) != 1)
        return BAD_NUMBER_INPUTTED;
    
    if (rval < 1)
        return BAD_NUMBER_INPUTTED;
    
    if (rval * lval == 1)
    {
        printf("1\n");
        return NO_ERROR;
    }
    
    node_t *l_fnum = factorize(lval);
    node_t *r_fnum = factorize(rval);
    
    node_t *res = multiplication(l_fnum, r_fnum);

    if (res == NULL)
    {
        full_clear_list(&l_fnum);
        full_clear_list(&r_fnum);
        return ALLOC_ERROR;
    }

    res = sort(res, num_cmp);

    print_fact_list(res);

    full_clear_list(&l_fnum);
    full_clear_list(&r_fnum);
    full_clear_list(&res);


    return NO_ERROR;
}

int sqr_cmd(void)
{
    int val;

    if (scanf("%d", &val) != 1)
        return BAD_NUMBER_INPUTTED;
    
    if (val < 1)
        return BAD_NUMBER_INPUTTED;
    
    if (val == 1)
    {
        printf("1\n");
        return NO_ERROR;
    }

    node_t *fval = factorize(val);

    if (fval == NULL)
        return ALLOC_ERROR;
    
    fval = sqr(fval);

    fval = sort(fval, num_cmp);
    
    print_fact_list(fval);

    full_clear_list(&fval);

    return NO_ERROR;
}

int div_cmd(void)
{
    int lval;

    if (scanf("%d", &lval) != 1)
        return BAD_NUMBER_INPUTTED;
    
    if (lval < 1)
        return BAD_NUMBER_INPUTTED;

    int rval;

    if (scanf("%d", &rval) != 1)
        return BAD_NUMBER_INPUTTED;
    
    if (rval < 1)
        return BAD_NUMBER_INPUTTED;

    // 1 1 | a 1 | 1 a

    if (lval * rval == 1)
    {
        printf("1\n");
        return NO_ERROR;
    }
    
    node_t *l_fnum = factorize(lval);

    if (l_fnum == NULL)
        return ALLOC_ERROR;

    node_t *r_fnum = factorize(rval);

    if (r_fnum == NULL)
    {
        if (rval == 1)
        {
            l_fnum = sort(l_fnum, num_cmp);
            print_fact_list(l_fnum);
            full_clear_list(&l_fnum);
            return NO_ERROR;
        }

        full_clear_list(&l_fnum);

        return ALLOC_ERROR;
    }

    node_t *res = NULL;
    
    if (division(l_fnum, r_fnum, &res))
    {
        full_clear_list(&l_fnum);
        full_clear_list(&r_fnum);
        ERROR_PRINT("Division error\n");
        return DIVISION_ERR;
    }

    res = sort(res, num_cmp);
    
    print_fact_list(res);

    full_clear_list(&l_fnum);
    full_clear_list(&r_fnum);
    full_clear_list(&res);

    return NO_ERROR;
}
