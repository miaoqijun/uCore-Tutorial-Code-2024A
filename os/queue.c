#include "queue.h"
#include "defs.h"

void init_queue(struct queue *q)
{
	q->front = q->tail = 0;
	q->empty = 1;
}

void push_queue(struct queue *q, int value, int priority)
{
	if (!q->empty && q->front == q->tail) {
		panic("queue shouldn't be overflow");
	}
	int i;
	q->empty = 0;
	for(i = q->tail; i != q->front; i = (i - 1) % NPROC) {
		if (priority >= q->priority[i - 1])
			break;
		q->data[i] = q->data[(i - 1) % NPROC];
		q->priority[i] = q->priority[(i - 1) % NPROC];
	}
	q->data[i] = value;
	q->priority[i] = priority;
	q->tail = (q->tail + 1) % NPROC;
}

int pop_queue(struct queue *q)
{
	if (q->empty)
		return -1;
	int value = q->data[q->front];
	q->front = (q->front + 1) % NPROC;
	if (q->front == q->tail)
		q->empty = 1;
	return value;
}
