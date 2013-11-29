/*
 * =====================================================================================
 *
 *       Filename:  heapsort.c
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  2013年10月31日 14时46分08秒
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  YOUR NAME (), 
 *   Organization:  
 *
 * =====================================================================================
 */
#include <stdlib.h>

//#define PARENT(i)       ((i) / 2)       //返回其父节点
#define LEFT(i)         (2 * (i) + 1)     //返回其左孩子节点
#define RIGHT(i)        (2 * (i) + 2)     //返回其右孩子节点
#define exchange(a, b)  {(a) = (a) + (b); (b) = (a) - (b); (a) = (a) - (b);}

int heapsize, length;

void
max_heapify(int *A, int i)
{
    /*
     * 从A[i], A[LEFT(i)], A[RIGHT(i)]中选出最大的，
     * 并将其下标存储在largest中。如果A[i]是最大的
     * 那么以i为根结点的子树已经是最大堆，程序结束。
     * 否则最大元素是i的某个孩子节点，则交换A[i]和
     * A[largest]的值，然后递归向下因为刚刚的改动
     * 可能会违反最大堆性质。
     */
    int     l, r, largest;

    l = LEFT(i);
    r = RIGHT(i);

    if (l < heapsize && A[l] > A[i]) {
        largest = l;
    } else {
        largest = i;
    }

    if (r < heapsize && A[r] > A[largest]) {
        largest = r;
    }

    if (largest != i) {
        exchange(A[i], A[largest]);
        max_heapify(A, largest);
    }
}

void
build_maxheap(int *A)
{
    /*
     * 子数组A(n / 2 + 1..n)中的元素都是树的叶节点，
     * 该过程对树中的其他节点都调用一次max_heapify。
     */
    int     i;

    for (i =  (length - 1) / 2; i >= 0; i--) {
        max_heapify(A, i);
    }
}

void
heapsort(int *A)
{
    /*
     * 数组中的最大元素总在根节点A[0]中，把它与A[i]交换，
     * 我们可以让该元素放到正确的位置。然后通过heapsize-1
     * 来从堆中去掉该节点。在交换完毕后，剩余的节点可能会
     * 违反最大堆性质，所以调用max_heapify维护最大堆
     */
    int     i;

    build_maxheap(A);
    for (i = length - 1; i >= 1; i--) {
        exchange(A[0], A[i]);
        heapsize = heapsize - 1;
        max_heapify(A, 0);
    }
}

int
main(void)
{
    int i;
    int A[] = {4, 1, 3, 2, 16, 9, 10, 14, 8, 7};

    heapsize  = sizeof(A) / sizeof(int);
    length = heapsize;

    heapsort(A);

    for (i = 0; i < 10; i++)
        printf("%d ", A[i]);
    printf("\n");
    
    return(0);
}
