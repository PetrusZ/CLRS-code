/*
 * =====================================================================================
 *
 *       Filename:  merge_sort.c
 *
 *    Description:
 *
 *        Version:  1.0
 *        Created:  2013年10月27日 23时03分33秒
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  YOUR NAME (),
 *   Organization:
 *
 * =====================================================================================
 */
#include <stdlib.h>

#define MAX     65535


void
merge(int *A, int p, int q, int r)
{
    /* 数组A[n], p、q和r都是数组下标，满足p <= q < r。
     * 假设数组A[p..q]和A[q+1..r]都已经排好序。函数合并
     * 这两个子数组形成单一的已排好序的子数组并代替当前的子数组A[p..r]。
     */

    int     n1, n2, i, j, k;
    //int     *L = NULL, *R = NULL;

    n1 = q - p + 1;
    n2 = r - q;

    //L = (int *)malloc(sizeof(int) * n1);
    //R = (int *)malloc(sizeof(int) * n2);

    int     L[n1 + 1], R[n2 + 1];

    for (i = 0; i < n1; i++)
        L[i] = A[p + i];
    for (j = 0; j < n2; j++)
        R[j] = A[q + j + 1];
    L[i] = MAX;
    R[j] = MAX;

    i = j  = 0;

    for (k = p ; k <= r; k++) {
        if (L[i] <= R[j])
            A[k] = L[i++];
        else
            A[k] = R[j++];
    }

    //free(L);
    //free(R);
}

void
merge_sort(int *A, int p, int r)
{
    int     q;

    if (p < r) {
        q = (p + r) / 2;
        merge_sort(A, p, q);
        merge_sort(A, q + 1, r);
        merge(A, p, q, r);
    }
}
