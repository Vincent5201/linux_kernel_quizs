#include <assert.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct __node {
    struct __node *left, *right;
    struct __node *next, *last;
    long value;
} node_t;

void list_add(node_t *list, node_t *node_t)
{
    node_t->next = list;
    node_t->last = NULL;
    if (list)
        list->last = node_t;
    list = node_t;
}

node_t *list_tail(node_t **left)
{
    while ((*left) && (*left)->next)
        left = &((*left)->next);
    return *left;
}

int list_length(node_t **left)
{
    int n = 0;
    while (*left) {
        ++n;
        left = &((*left)->next);
    }
    return n;
}

node_t *list_construct(node_t *list, int n)
{
    node_t *node = malloc(sizeof(node_t));
    node->next = list;
    if (list)
        list->last = node;
    node->last = NULL;
    node->value = n;
    return node;
}

void list_free(node_t **list)
{
    node_t *node = (*list)->next;
    while (*list) {
        free(*list);
        *list = node;
        if (node)
            node = node->next;
    }
}

node_t *list_find_mid(node_t *L, node_t *R)
{
    node_t* fast = L;
    node_t* slow = L;
    while (fast != R && fast->next != R) {
        fast = fast->next->next;
        slow = slow->next;
    }
    return slow;
}

/* Verify if list is order */
static bool list_is_ordered(node_t *list)
{       
    bool first = true;
    int value;
    while (list) {
        if (first) {
            value = list->value;
            first = false;
        } else {
            if (list->value < value)
                return false;
            value = list->value;
        }
        list = list->next;
    }
    return true;
}

/* shuffle array, only work if n < RAND_MAX */
void shuffle(int *array, size_t n)
{
    if (n <= 0)
        return;

    for (size_t i = 0; i < n - 1; i++) {
        size_t j = i + rand() / (RAND_MAX / (n - i) + 1);
        int t = array[j];
        array[j] = array[i];
        array[i] = t;
    }
}

void quick_sort_medium3(node_t **list)
{
    int n = list_length(list);
    int value;
    int i = 0;
    int max_level = 2 * n;
    node_t *begin[max_level], *end[max_level];
    node_t *result = NULL, *left = NULL, *right = NULL;
    
    begin[0] = *list;
    end[0] = list_tail(list);
            
    while (i >= 0) {
        node_t *L = begin[i], *R = end[i];
        if (L != R) {
            node_t *pivot;
            node_t *p;
            long v1, v2, v3;
            node_t *mid = list_find_mid(L, R);
            v1 = L->value;
            v2 = mid->value;
            v3 = R->value;

            if (R == mid) {
                pivot = L;
                p = L->next;
                pivot->next = NULL;
                value = pivot->value;
            } else {
                if (v1 >= v2 && v2 >= v3) {
                    node_t *tmp = mid->next;
                    mid->next->last = mid->last;
                    mid->last->next = tmp;
                    value = v2;
                    pivot = mid;
                    p = L;
                    pivot->last = pivot->next = NULL;
                } else if (v2 >= v1 && v1 >= v3) {
                    value = v1;
                    pivot = L;
                    p = L->next;
                    pivot->next->last = NULL;
                    pivot->next = NULL;
                } else {
                    value = v3;
                    pivot = R;
                    p = L;
                    pivot->last->next = NULL;
                    pivot->last = NULL;
                }
            }

            while (p) {
                node_t *n = p;
                p = p->next;
                list_add(n->value > value ? right : left, n);
            }

            begin[i] = left;
            end[i] = list_tail(&left);
            begin[i + 1] = pivot;
            end[i + 1] = pivot;
            begin[i + 2] = right;
            end[i + 2] = list_tail(&right);

            left = right = NULL;
            i += 2;
        } else {
            if (L)
                list_add(result, L);
            i--;
        }
    }
    *list = result;
}


int main(int argc, char **argv)
{
    node_t *list = NULL;

    size_t count = 10;

    int *test_arr = malloc(sizeof(int) * count);
    for (int i = 0; i < count; ++i)
        test_arr[i] = i;
    shuffle(test_arr, count);
    
    while (count--)
        list = list_construct(list, test_arr[count]);
    
    quick_sort_medium3(&list);
    if (list_is_ordered(list)) {
        printf("success\n");
    } else {
        printf("fail\n");
    }

    list_free(&list);

    free(test_arr);

    return 0;
}
