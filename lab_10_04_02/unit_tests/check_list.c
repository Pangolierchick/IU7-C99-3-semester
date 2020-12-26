#include <check.h>
#include <stdio.h>
#include <stdlib.h>
#include "list.h"

#define TO_INT(node) *((int *) node->data)

START_TEST(pushback_neg_1)
{
    int arr[] = { 1, 2, 3, 4 };
    node_t *list = init_node(arr);
    int res = pushback(&list, NULL);

    ck_assert_int_gt(res, 0);

    clear_list(&list);
}
END_TEST

START_TEST(pushback_neg_2)
{
    int arr[] = { 1, 2, 3, 4 };
    node_t *list = init_node(arr);
    int res = pushback(NULL, arr + 1);

    ck_assert_int_gt(res, 0);

    clear_list(&list);
}
END_TEST

START_TEST(pushback_pos_1)
{
    int arr[] = { 1, 2, 3, 4 };
    node_t *list = NULL;

    int res = pushback(&list, arr + 1);

    ck_assert_int_eq(res, 0);
    ck_assert_int_eq(TO_INT(list), *(arr + 1));

    clear_list(&list);
}
END_TEST

START_TEST(pushback_pos_2)
{
    int arr[] = { 1, 2, 3, 4 };
    node_t *list = NULL;

    int res = 0;
    for (int i = 0; i < 4; i++)
        res |= pushback(&list, arr + i);


    node_t *p = list;

    for (int i = 0; i < 4; i++)
    {
        ck_assert_int_eq(TO_INT(p), *(arr + i));
        p = p->next;
    }

    ck_assert_int_eq(res, 0);

    clear_list(&list);
}
END_TEST

Suite *list_pushback(void)
{
    Suite *s;
    TCase *tc_pos;
    TCase *tc_neg;

    s = suite_create("List pushback");

    tc_pos = tcase_create("positives");

    tcase_add_test(tc_pos, pushback_pos_1);
    tcase_add_test(tc_pos, pushback_pos_2);

    suite_add_tcase(s, tc_pos);

    tc_neg = tcase_create("negatives");

    tcase_add_test(tc_neg, pushback_neg_1);
    tcase_add_test(tc_neg, pushback_neg_2);

    suite_add_tcase(s, tc_neg);

    return s;
}


int int_cmp(const void *a, const void *b)
{
    const int *ia = a;
    const int *ib = b;

    return *ia - *ib;
}

int int_cmp_rev(const void *a, const void *b)
{
    const int *ia = a;
    const int *ib = b;

    return *ib - *ia;
}

START_TEST(find_neg_1)
{
    int arr[] = { 1, 2, 3, 4 };
    node_t *node = init_node(arr);
    
    void *res = find(node, NULL, int_cmp);

    ck_assert_ptr_null(res);

    clear_list(&node);
}
END_TEST

START_TEST(find_neg_2)
{
    int arr[] = { 1, 2, 3, 4 };
    node_t *node = init_node(arr);
    
    void *res = find(node, arr + 1, NULL);

    ck_assert_ptr_null(res);

    clear_list(&node);
}
END_TEST

START_TEST(find_neg_3)
{
    int arr[] = { 1, 2, 3, 4 };
    node_t *node = init_node(arr);
    
    void *res = find(NULL, arr + 1, int_cmp);

    ck_assert_ptr_null(res);

    clear_list(&node);
}
END_TEST


START_TEST(find_pos_1)
{
    int arr[] = { 1, 2, 3, 4 };
    node_t *node = init_node(arr);
    
    node_t *res = find(node, arr, int_cmp);

    ck_assert_ptr_nonnull(res);
    ck_assert_int_eq(TO_INT(res), *arr);

    clear_list(&node);
}
END_TEST


START_TEST(find_pos_2)
{
    int arr[] = { 1, 2, 3, 4 };
    node_t *node = init_node(arr);
    pushback(&node, arr + 1);
    pushback(&node, arr + 2);
    pushback(&node, arr + 3);
    
    node_t *res = find(node, arr + 3, int_cmp);

    ck_assert_ptr_nonnull(res);
    ck_assert_int_eq(TO_INT(res), *(arr + 3));

    clear_list(&node);
}
END_TEST

START_TEST(find_pos_3)
{
    int arr[] = { 1, 2, 3, 4, 4, 4, 4};
    node_t *node = NULL;

    for (int i = 0; i < 7; i++)
        pushback(&node, arr + i);
    
    node_t *res = find(node, arr + 6, int_cmp);

    ck_assert_ptr_nonnull(res);
    ck_assert_ptr_eq(res->data, arr + 3);
    ck_assert_int_eq(TO_INT(res), *(arr + 6));

    clear_list(&node);
}
END_TEST


START_TEST(find_pos_4)
{
    int val = 100;
    int arr[] = { 1, 2, 3, 4, 4, 4, 4};
    node_t *node = NULL;

    for (int i = 0; i < 7; i++)
        pushback(&node, arr + i);
    
    node_t *res = find(node, &val, int_cmp);

    ck_assert_ptr_null(res);

    clear_list(&node);
}
END_TEST


Suite *list_find(void)
{
    Suite *s;
    TCase *tc_pos;
    TCase *tc_neg;

    s = suite_create("List find");

    tc_pos = tcase_create("positives");

    tcase_add_test(tc_pos, find_pos_1);
    tcase_add_test(tc_pos, find_pos_2);
    tcase_add_test(tc_pos, find_pos_3);
    tcase_add_test(tc_pos, find_pos_4);
    

    suite_add_tcase(s, tc_pos);

    tc_neg = tcase_create("negatives");

    tcase_add_test(tc_neg, find_neg_1);
    tcase_add_test(tc_neg, find_neg_2);
    tcase_add_test(tc_neg, find_neg_3);

    suite_add_tcase(s, tc_neg);

    return s;
}

int cmp_list_arr(node_t *list, int *arr, int len)
{
    node_t *p = list;
    int res = 0;

    for (int i = 0; i < len; i++)
    {
        if (p == NULL)
            return res;


        res += int_cmp(p->data, arr + i) != 0;
        p = p->next;
    }

    return res;
}

START_TEST(insert_pos_1)
{
    int res[] = { 1, 2, 3, 5, 4 };
    int arr[] = { 1, 2, 3, 4 };
    node_t *node = NULL;

    for (int i = 0; i < 4; i++)
        pushback(&node, arr + i);
    
    node_t *new = calloc(1, sizeof(node_t));

    new->data = res + 3;

    node_t *before = node->next->next->next;

    insert(&node, new, before);

    ck_assert_int_eq(cmp_list_arr(node, res, 5), 0);

    clear_list(&node);
}
END_TEST


START_TEST(insert_pos_2)
{
    int res[] = { 1, -2, 2, 3, 4 };
    int arr[] = { 1, 2, 3, 4 };
    node_t *node = NULL;

    for (int i = 0; i < 4; i++)
        pushback(&node, arr + i);
    
    node_t *new = calloc(1, sizeof(node_t));

    new->data = res + 1;

    node_t *before = node->next;

    insert(&node, new, before);

    ck_assert_int_eq(cmp_list_arr(node, res, 5), 0);

    clear_list(&node);
}
END_TEST

START_TEST(insert_pos_3)
{
    int res[] = { -5, 1, 2, 3, 4 };
    int arr[] = { 1, 2, 3, 4 };
    node_t *node = NULL;

    for (int i = 0; i < 4; i++)
        pushback(&node, arr + i);
    
    node_t *new = calloc(1, sizeof(node_t));

    new->data = res;

    node_t *before = node;

    insert(&node, new, before);

    ck_assert_int_eq(cmp_list_arr(node, res, 5), 0);

    clear_list(&node);
}
END_TEST

START_TEST(insert_neg_1)
{
    int res[] = { -5, 1, 2, 3, 4 };
    int arr[] = { 1, 2, 3, 4 };
    node_t *node = NULL;

    for (int i = 0; i < 4; i++)
        pushback(&node, arr + i);
    
    node_t *new = calloc(1, sizeof(node_t));

    new->data = res;

    insert(&node, new, NULL);

    clear_list(&node);
    free(new);
}
END_TEST

START_TEST(insert_neg_2)
{
    int res[] = { -5, 1, 2, 3, 4 };
    int arr[] = { 1, 2, 3, 4 };
    node_t *node = NULL;

    for (int i = 0; i < 4; i++)
        pushback(&node, arr + i);
    
    node_t *new = calloc(1, sizeof(node_t));

    new->data = res;

    node_t *before = node;

    insert(&node, NULL, before);

    clear_list(&node);
    free(new);
}
END_TEST


START_TEST(insert_neg_3)
{
    int res[] = { -5, 1, 2, 3, 4 };
    int arr[] = { 1, 2, 3, 4 };
    node_t *node = NULL;

    for (int i = 0; i < 4; i++)
        pushback(&node, arr + i);
    
    node_t *new = calloc(1, sizeof(node_t));

    new->data = res;

    node_t *before = node;

    insert(NULL, new, before);

    clear_list(&node);
    free(new);
}
END_TEST

START_TEST(insert_neg_4)
{
    int res[] = { -5, 1, 2, 3, 4 };
    node_t *node = NULL;
    
    node_t *new = calloc(1, sizeof(node_t));

    new->data = res;

    node_t *before = node;

    insert(&node, new, before);

    clear_list(&node);
    free(new);
}
END_TEST


Suite *list_insert(void)
{
    Suite *s;
    TCase *tc_pos;
    TCase *tc_neg;

    s = suite_create("List insert");

    tc_pos = tcase_create("positives");

    tcase_add_test(tc_pos, insert_pos_1);
    tcase_add_test(tc_pos, insert_pos_2);
    tcase_add_test(tc_pos, insert_pos_3);
    
    suite_add_tcase(s, tc_pos);

    tc_neg = tcase_create("negatives");

    tcase_add_test(tc_neg, insert_neg_1);
    tcase_add_test(tc_neg, insert_neg_2);
    tcase_add_test(tc_neg, insert_neg_3);
    tcase_add_test(tc_neg, insert_neg_4);

    suite_add_tcase(s, tc_neg);

    return s;
}

START_TEST(rmv_dpl_neg_1)
{
    node_t *node = NULL;

    remove_duplicates(NULL, int_cmp);

    clear_list(&node);
}
END_TEST

START_TEST(rmv_dpl_neg_2)
{
    node_t *node = NULL;

    remove_duplicates(&node, int_cmp);

    clear_list(&node);
}
END_TEST

START_TEST(rmv_dpl_neg_3)
{
    int arr[] = { 1, 2, 3, 4 };
    node_t *node = init_node(arr);

    remove_duplicates(&node, NULL);

    clear_list(&node);
}
END_TEST


START_TEST(rmv_dpl_pos_1)
{
    int res[] = { 1, 2, 3, 4 };
    int arr[] = { 1, 2, 3, 4 };
    node_t *node = NULL;

    for (int i = 0; i < 4; i++)
        pushback(&node, arr + i);

    remove_duplicates(&node, int_cmp);

    ck_assert_int_eq(cmp_list_arr(node, res, 4), 0);

    clear_list(&node);
}
END_TEST

START_TEST(rmv_dpl_pos_2)
{
    int res[] = { 1 };
    int arr[] = { 1 };
    node_t *node = init_node(arr);

    remove_duplicates(&node, int_cmp);

    ck_assert_int_eq(cmp_list_arr(node, res, 1), 0);

    clear_list(&node);
}
END_TEST

START_TEST(rmv_dpl_pos_3)
{
    int res[] = { 1, 2};
    int arr[] = { 1, 1, 1, 1, 2};
    node_t *node = NULL;

    for (int i = 0; i < 5; i++)
        pushback(&node, arr + i);

    remove_duplicates(&node, int_cmp);

    ck_assert_int_eq(cmp_list_arr(node, res, 2), 0);

    clear_list(&node);
}
END_TEST

START_TEST(rmv_dpl_pos_4)
{
    int res[] = { 1 };
    int arr[] = { 1, 1, 1, 1 };
    node_t *node = NULL;

    for (int i = 0; i < 4; i++)
        pushback(&node, arr + i);

    remove_duplicates(&node, int_cmp);

    ck_assert_int_eq(cmp_list_arr(node, res, 1), 0);

    clear_list(&node);
}
END_TEST

Suite *list_rmv_dpl(void)
{
    Suite *s;
    TCase *tc_pos;
    TCase *tc_neg;

    s = suite_create("List remove duplicated");

    tc_pos = tcase_create("positives");

    tcase_add_test(tc_pos, rmv_dpl_pos_1);
    tcase_add_test(tc_pos, rmv_dpl_pos_2);
    tcase_add_test(tc_pos, rmv_dpl_pos_3);
    tcase_add_test(tc_pos, rmv_dpl_pos_4);
    
    
    suite_add_tcase(s, tc_pos);

    tc_neg = tcase_create("negatives");

    tcase_add_test(tc_neg, rmv_dpl_neg_1);
    tcase_add_test(tc_neg, rmv_dpl_neg_2);
    tcase_add_test(tc_neg, rmv_dpl_neg_3);

    suite_add_tcase(s, tc_neg);

    return s;
}


START_TEST(sort_neg_1)
{
    node_t *list_res = sort(NULL, int_cmp);

    ck_assert_ptr_null(list_res);
}
END_TEST


START_TEST(sort_neg_2)
{
    int arr[] = { 1, 1, 1, 1 };
    node_t *node = init_node(arr);

    node_t *list_res = sort(node, NULL);

    ck_assert_ptr_null(list_res);

    clear_list(&node);
}
END_TEST


START_TEST(sort_pos_1)
{
    int res[] = { 1, 2, 3, 4 };
    int arr[] = { 1, 2, 3, 4 };
    node_t *node = NULL;

    for (int i = 0; i < 4; i++)
        pushback(&node, arr + i);

    node_t *list_res = sort(node, int_cmp);

    ck_assert_ptr_nonnull(list_res);
    ck_assert_int_eq(cmp_list_arr(list_res, res, 4), 0);

    clear_list(&list_res);
}
END_TEST

START_TEST(sort_pos_2)
{
    int res[] = { 1, 2, 3, 4 };
    int arr[] = { 4, 3, 2, 1 };
    node_t *node = NULL;

    for (int i = 0; i < 4; i++)
        pushback(&node, arr + i);

    node_t *list_res = sort(node, int_cmp);

    ck_assert_ptr_nonnull(list_res);
    ck_assert_int_eq(cmp_list_arr(list_res, res, 4), 0);

    clear_list(&list_res);
}
END_TEST

START_TEST(sort_pos_3)
{
    int res[] = { 4, 3, 2, 1 };
    int arr[] = { 1, 2, 3, 4 };
    node_t *node = NULL;

    for (int i = 0; i < 4; i++)
        pushback(&node, arr + i);

    node_t *list_res = sort(node, int_cmp_rev);

    ck_assert_ptr_nonnull(list_res);
    ck_assert_int_eq(cmp_list_arr(list_res, res, 4), 0);

    clear_list(&list_res);
}
END_TEST

START_TEST(sort_pos_4)
{
    int res[] = { 1 };
    int arr[] = { 1 };
    node_t *node = NULL;

    for (int i = 0; i < 1; i++)
        pushback(&node, arr + i);

    node_t *list_res = sort(node, int_cmp_rev);

    ck_assert_ptr_nonnull(list_res);
    ck_assert_int_eq(cmp_list_arr(list_res, res, 1), 0);

    clear_list(&list_res);
}
END_TEST

Suite *list_sort(void)
{
    Suite *s;
    TCase *tc_pos;
    TCase *tc_neg;

    s = suite_create("List sort");

    tc_pos = tcase_create("positives");

    
    tcase_add_test(tc_pos, sort_pos_1);
    tcase_add_test(tc_pos, sort_pos_2);
    tcase_add_test(tc_pos, sort_pos_3);
    tcase_add_test(tc_pos, sort_pos_4);
    
    
    suite_add_tcase(s, tc_pos);

    tc_neg = tcase_create("negatives");

    tcase_add_test(tc_neg, sort_neg_1);
    tcase_add_test(tc_neg, sort_neg_2);

    suite_add_tcase(s, tc_neg);

    return s;
}
