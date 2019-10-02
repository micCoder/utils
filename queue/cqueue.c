#include <stdio.h>
#include <stdlib.h>
#include "cqueue.h"

struct cqueue_ {
    int head;
    int tail;
    int cap;
    void *dat[0];
};

cqueue_t *cqueue_new(int cap)
{
    cqueue_t *cq = NULL;

    if (cap <= 0)
        return NULL;

    cq = (cqueue_t *)calloc(1, sizeof(cqueue_t) + sizeof(void *) * cap);
    if (cq) {
        cq->head = -1;
        cq->tail = -1;
        cq->cap = cap;
    }

    return cq;
}

void cqueue_destroy(cqueue_t *cq)
{
    if (cq)
        free(cq);
}

int cqueue_enqueue(cqueue_t *cq, void *elem)
{
    if (!cq || !elem)
        return 0;

    if (cqueue_is_full(cq))
        return 0;

    if (cqueue_is_empty(cq))
        cq->head = 0;

    cq->tail = (cq->tail + 1) % cq->cap;
    cq->dat[cq->tail] = elem;

    return 1;
}

void *cqueue_dequeue(cqueue_t *cq)
{
    void *elem = NULL;

    if (!cq)
        return NULL;

    if (cqueue_is_empty(cq))
        return NULL;

    elem = cq->dat[cq->head];
    if (cq->head == cq->tail) {
        cq->head = -1;
        cq->tail = -1;
    } else {
        cq->head = (cq->head + 1) % cq->cap;
    }

    return elem;
}

void *cqueue_head(cqueue_t *cq)
{
    if (cqueue_is_empty(cq))
        return NULL;

    return cq->dat[cq->head];
}

void *cqueue_tail(cqueue_t *cq)
{
    if (cqueue_is_empty(cq))
        return NULL;

    return cq->dat[cq->tail];
}

int cqueue_is_empty(cqueue_t *cq)
{
    return cq->head == -1;
}

int cqueue_is_full(cqueue_t *cq)
{
    return (cq->tail + 1) % cq->cap == cq->head;
}

int cqueue_size(cqueue_t *cq)
{
    if (cqueue_is_empty(cq))
        return 0;

    if (cq->head <= cq->tail)
        return cq->tail - cq->head + 1;
    else
        return (cq->cap - cq->head + cq->tail + 1);
}
