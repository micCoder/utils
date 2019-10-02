#ifdef TEST_CQUEUE
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../cqueue/cqueue.h"

#define TEST_QUEUE_SIZE 5
#define TEST_LOG(fmt, ...) fprintf(stdout, "Func[%s]: "fmt, __func__, __VA_ARGS__)

void test_empty()
{
    cqueue_t *q = cqueue_new(TEST_QUEUE_SIZE);
    if (q) {
        if (cqueue_is_empty(q) && cqueue_size(q) == 0) {
            TEST_LOG("%s", "test success\n");
        } else {
            TEST_LOG("%s", "test failed\n");
        }

        int elem = 123;
        if (cqueue_enqueue(q, &elem)) {
            if (cqueue_dequeue(q)) {
                if (cqueue_is_empty(q) && cqueue_size(q) == 0) {
                    TEST_LOG("%s", "test success\n");
                } else {
                    TEST_LOG("%s", "test failed\n");
                }
            } else {
                TEST_LOG("%s", "dequeue failed\n");
            }
        } else {
            TEST_LOG("%s", "enqueue failed\n");
        }

        cqueue_destroy(q);
    }
}

void test_full()
{
    cqueue_t *q = cqueue_new(TEST_QUEUE_SIZE);
    if (q) {
        int elem[TEST_QUEUE_SIZE] = {1, 2, 3, 4, 5};
        int i = 0;
        for (i = 0; i < TEST_QUEUE_SIZE; i++) {
            if (!cqueue_enqueue(q, &elem[i])) {
                TEST_LOG("%s", "enqueue failed\n");
            }
        }

        if (cqueue_is_full(q) && cqueue_size(q) == TEST_QUEUE_SIZE) {
            TEST_LOG("%s", "test success\n");
        } else {
            TEST_LOG("%s", "test failed\n");
        }

        cqueue_destroy(q);
    }
}

void test_head_lt_tail()
{
    cqueue_t *q = cqueue_new(TEST_QUEUE_SIZE);
    if (q) {
        int elem[2] = {1, 2};
        int i = 0;
        for (i = 0; i < 2; i++) {
            if (!cqueue_enqueue(q, &elem[i])) {
                TEST_LOG("%s", "enqueue failed\n");
            }
        }

        if (cqueue_size(q) == 2) {
            TEST_LOG("%s", "test success\n");
        } else {
            TEST_LOG("%s", "test failed\n");
        }

        cqueue_destroy(q);
    }
}

void test_head_eq_tail()
{
    cqueue_t *q = cqueue_new(TEST_QUEUE_SIZE);
    if (q) {
        int elem[1] = {1};
        int i = 0;
        for (i = 0; i < 1; i++) {
            if (!cqueue_enqueue(q, &elem[i])) {
                TEST_LOG("%s", "enqueue failed\n");
            }
        }

        if (cqueue_size(q) == 1) {
            TEST_LOG("%s", "test success\n");
        } else {
            TEST_LOG("%s", "test failed\n");
        }

        cqueue_destroy(q);
    }
}

void test_head_gt_tail()
{
    cqueue_t *q = cqueue_new(TEST_QUEUE_SIZE);
    if (q) {
        int elem[TEST_QUEUE_SIZE+1] = {1, 2, 3, 4, 5, 6};
        int i = 0;
        for (i = 0; i < TEST_QUEUE_SIZE; i++) {
            if (!cqueue_enqueue(q, &elem[i])) {
                TEST_LOG("%s", "enqueue failed\n");
            }
        }

        if (cqueue_is_full(q) && cqueue_size(q) == TEST_QUEUE_SIZE) {
            cqueue_dequeue(q);
            cqueue_enqueue(q, &elem[i]);
            if (cqueue_is_full(q) && cqueue_size(q) == TEST_QUEUE_SIZE) {
                TEST_LOG("%s", "test success\n");
            } else {
                TEST_LOG("%s", "test failed\n");
            }
        } else {
            TEST_LOG("%s", "test failed\n");
        }

        cqueue_destroy(q);
    }
}

void test_enqueue_dequeue()
{
    cqueue_t *q = cqueue_new(TEST_QUEUE_SIZE);
    if (q) {
        int elem[TEST_QUEUE_SIZE] = {1, 2, 3, 4, 5};
        int i = 0;
        for (i = 0; i < TEST_QUEUE_SIZE; i++) {
            if (!cqueue_enqueue(q, &elem[i])) {
                TEST_LOG("%s", "enqueue failed\n");
            }
        }

        int flag = 0;
        int *p = NULL;
        int size = cqueue_size(q);
        for (i = 0; i < size; i++) {
            p = cqueue_dequeue(q);
            TEST_LOG("[%d]=%d\n", i, *p);

            if (elem[i] != *p) {
                flag = 1;
            }
        }

        if (flag) {
            TEST_LOG("%s", "test failed\n");
        } else {
            TEST_LOG("%s", "test success\n");
        }

        cqueue_destroy(q);
    }
}

int main(int argc, char **arv)
{
    test_empty();

    test_full();

    test_enqueue_dequeue();

    test_head_lt_tail();

    test_head_eq_tail();

    test_head_gt_tail();

    return 0;
}
#endif
