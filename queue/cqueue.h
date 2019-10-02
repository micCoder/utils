#ifndef CIRCLE_QUEUE_INCLUDE_FILE_
#define CIRCLE_QUEUE_INCLUDE_FILE_

#ifdef __cplusplus
extern "C" {
#endif

struct cqueue_;
typedef struct cqueue_ cqueue_t;

cqueue_t *cqueue_new(int cap);
void cqueue_destory(cqueue_t *cq);

int cqueue_enqueue(cqueue_t *cq, void *elem);
void *cqueue_dequeue(cqueue_t *cq);

void *cqueue_head(cqueue_t *cq);
void *cqueue_tail(cqueue_t *cq);

int cqueue_is_empty(cqueue_t *cq);
int cqueue_is_full(cqueue_t *cq);
int cqueue_size(cqueue_t *cq);

#ifdef __cplusplus
}
#endif

#endif
