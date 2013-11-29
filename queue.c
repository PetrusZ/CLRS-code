/*
 * =====================================================================================
 *
 *       Filename:  queue.c
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  2013年11月04日 15时34分50秒
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  YOUR NAME (), 
 *   Organization:  
 *
 * =====================================================================================
 */ 
#include <stdlib.h>
#include <stdio.h>

#define queuesize   12

typedef struct {
    int     *queue;
    int     tail;
    int     head;
    int     length;
}QUEUE;

void
queue_init(QUEUE *Q)
{
    Q->tail = 0;
    Q->head = 0;
    Q->queue = (int *)malloc(sizeof(int) * queuesize);
    Q->length = 0;
}

void
enqueue(QUEUE *Q, int x)
{
    if (Q->length == queuesize)
        printf("error: queue overflow\n");
    else {
        Q->queue[Q->tail] = x;
        if (Q->tail == queuesize - 1)
            Q->tail = 0;
        else
            Q->tail++;
        Q->length++;
    }
}

int
dequeue(QUEUE *Q)
{
    int     x;

    if (Q->length == 0)
        printf("error: queue underflow\n");
    else {
        x = Q->queue[Q->head];
        if (Q->head == queuesize - 1)
            Q->head = 0;
        else
            Q->head++;
        Q->length--;
        return x;
    }
}

int
main(void)
{
    int     i;
    QUEUE   Q;

    queue_init(&Q);
    enqueue(&Q, 24);
    enqueue(&Q, 83);
    enqueue(&Q, 1);
    enqueue(&Q, 23);
    enqueue(&Q, 48);
    enqueue(&Q, 12);
    enqueue(&Q, 94);

    printf("after enqueue: ");
    for (i = Q.head; i != Q.tail; i++) {
        if (i == queuesize - 1)
            i = 0;
        printf("%d ", Q.queue[i]);
    }
    printf("\n");

    dequeue(&Q);
    dequeue(&Q);
    dequeue(&Q);
    dequeue(&Q);
    dequeue(&Q);
    dequeue(&Q);
    dequeue(&Q);

    printf("after dequeue: ");
    for (i = Q.head; i != Q.tail; i++) {
        if (i == queuesize - 1)
            i = 0;
        printf("%d ", Q.queue[i]);
    }
    printf("\n");

    enqueue(&Q, 23);
    enqueue(&Q, 48);
    enqueue(&Q, 12);
    enqueue(&Q, 94);

    printf("after enqueue2: ");
    for (i = Q.head; i != Q.tail; i++) {
        if (i == queuesize - 1)
            i = 0;
        printf("%d ", Q.queue[i]);
    }
    printf("\n");
}
