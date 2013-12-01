/*
 * =====================================================================================
 *
 *       Filename:  priority_queue.c
 *
 *    Description:  最大优先的队列
 *
 *        Version:  1.0
 *        Created:  2013年10月31日 22时21分30秒
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  YOUR NAME (), 
 *   Organization:  
 *
 * =====================================================================================
 */
#include <stdlib.h>

#define PARENT(i)       ((i) / 2)       
#define LEFT(i)         (2 * (i) + 1)     
#define RIGHT(i)        (2 * (i) + 2)     
#define exchange(a, b)  {(a) = (a) + (b); (b) = (a) - (b); (a) = (a) - (b);}

#define MIN             -65535


int
heap_max(int *A)
{
    /*
     * 返回A中具有最大关键字的元素
     */
    return A[0];
}

int
heap_extract_max(int *A)
{
    /*
     * 去掉并返回A中具有最大关键字的元素
     */
    int     max;

    if (heapsize < 1) {
        printf("heap underflow\n");
        return(-1);
    }

    max = A[0];
    A[0] = A[heapsize];
    heapsize--;
    max_heapify(A, 0);
    return(max);
}

void
heap_increase_key(int *A, int i, int key)
{
    /*
     * 将元素i的关键字值增加到key，key不小于i的源关键字值
     */
    int     i;

    if (key < A[i]) {
        printf("new key is smaller than current key\n");
    }
    A[i] = key;
    while (i > 0 && A[PARENT(i)] < A[i]) {
        exchange(A[i], A[PARENT(i)]);
        i = PARENT(i);
    }
}

void
max_heap_insert(int *A, int key)
{
    /*
     * 把元素x插入集合A中
     */
    heapsize++;
    A[heapsize] = MIN;
    heap_increase_key(A, heapsize, key);
}
