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
void
merge(int *A, int p, int q, int r)
{
    /* 数组A[n], p、q和r都是数组下标，满足p <= q < r。
     * 假设数组A[p..q]和A[q+1..r]都已经排好序。函数合并
     * 这两个子数组形成单一的已排好序的子数组并代替当前的子数组A[p..r]。
     */

    int     n1, n2, i, j, k;

    n1 = q - p + 1;
    n2 = r - q;

    int     L[n1], R[n2];

    for (i = 0; i < n1; i++)
        L[i] = A[p + i];
    for (j = 0; j < n2; j++)
        R[j] = A[q + j + 1];

    i = j  = 0;
    k = p;

    while (i < n1 && j < n2) {
        if (L[i] <= R[j])
            A[k++] = L[i++];
        else
            A[k++] = R[j++];
    }

    for ( ; i < n1; i++)
        A[k++] = L[i];
    for ( ; j < n2; j++)
        A[k++] = R[j];

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
