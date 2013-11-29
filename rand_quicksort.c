/*
 * =====================================================================================
 *
 *       Filename:  quicksort.c
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  2013年11月03日 16时51分02秒
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  YOUR NAME (), 
 *   Organization:  
 *
 * =====================================================================================
 */
#include <stdlib.h>
 
#define exchange(a, b)  {(a) = (a) + (b); (b) = (a) - (b); (a) = (a) - (b);}
//exchange(a, b)不适用于同一个变量交换自己，交换结果会发生错误，值变为0。所以这回不使用这个宏。
 
int
partition(int *A, int p, int r)
{
    /*
     * 选择一个x=A[r]作为主元，并围绕它来划分子数组A[p..r]。
     * 最终分成小于等于主元的两个数组，A[p..i-1]和A[i+1..r]。
     */
    int x, i, j;
    int temp;
 
    x = A[r];
    i = p - 1;
 
    for (j = p; j < r; j++) {
        if (A[j] <= x) {
            i = i + 1;
            //exchange(A[i], A[j]);
            temp = A[j];
            A[j] = A[i];
            A[i] = temp;
        }
    }
    //exchange(A[i + 1], A[r]);
    temp = A[r];
    A[r] = A[i + 1];
    A[i + 1] = temp;
    return(i + 1);
}

int
rand_partition(int *A, int p, int r)
{
    int     i, temp;
    i = p + rand() % (r - p + 1);
    temp = A[r];
    A[r] = A[i];
    A[i] = temp;
    return(partition(A, p, r));
}

void
quicksort(int *A, int p ,int r)
{
    /*
     * 递归调用快速排序，对以数组进行排序。
     */
    int     q;
 
    if (p < r) {
        q = partition(A, p, r);
        quicksort(A, p, q-1);
        quicksort(A, q+1, r);
    }
}

void
rand_quicksort(int *A, int p, int r)
{
    int     q;
 
    if (p < r) {
        q = rand_partition(A, p, r);
        rand_quicksort(A, p, q - 1);
        rand_quicksort(A, q + 1, r);
    }
 
}

int
rand_select(int *A, int p, int r, int i)
{
    /*
     * 期望为线性的选择算法
     */
    int     k, q;

    if (p == r)
        return(A[p]);
    q = rand_partition(A, p, r);

    k = q - p + 1;
    if (i == k)         //the pivot value is the answer
        return(A[q]);
    else if (i < k)
        return rand_select(A, p, q - 1, i);
    else
        return rand_select(A, q + 1, r, i - k);
}

