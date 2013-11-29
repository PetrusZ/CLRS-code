/*
 * =====================================================================================
 *
 *       Filename:  select_wcliner.c
 *
 *    Description:  最坏情况为线性的选择算法
 *
 *        Version:  1.0
 *        Created:  2013年11月03日 17时19分59秒
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  YOUR NAME (), 
 *   Organization:  
 *
 * =====================================================================================
 */
#include <stdlib.h>

extern void insertion_sort(int *A);

SELECT(A, p, r, i) 
{
    // 步骤１、２
    count = ceiling(n/5);
    for i = 1 to count-1
        insertion sort A[(i-1)*5+1...i*5+1];
    insertion sort A[(count-1)*5+1...n];
    if count ==1
        return A[floor(n/2)];
    // 步骤３
    create array B;
    for i = 1 to count-1
        B[i] = A[(i-1)*5+3];
    B[count] = A[(count-1)*5 + floor((n - (count-1)*5)/2)];
    x = SELECT(B, 1, count, floor(count/2));
    // 步骤４
    q = PARTITION_X(A, p, r, i);
    k = q-p+1;
    // 步骤５
    if i == k
        return x;
    elseif i < k
        return SELECT(A, p, q-1, i);
    else
        return SELECT(A, q+1, r, i-k);
}

void
insertion_sort(int  *A, int p, int r)
{
    int     i, j;
    int     key;

    for (j = p + 1; j < r; j++) {
        key = A[j];
        //Insert A[j] into the sorted sequence A[1..j-1].
        i = j - 1;
        while ( i >= 0 && A[i] > key) {
            A[i + 1] = A[i];
            i = i - 1;
        }
        A[i + 1] = key;
    }
}

int
partition(int *A, int p, int r, int privot)
{
    int x, i, j;
    int temp;
 
    for (i = 0; i < r; i++) {
        if (A[i] == privot)
            break;
    }
    x = A[i];
    temp = A[i];
    A[i] = A[r];
    A[r] = A[i];
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
select(int *A, int p, int r, int i)
{
    int     i;
    int     *B;
    int     count, k, q;

    if (n % 5 == 0)
        count = sizeof(A) / 5;
    else
        count = sizeof(A) / 5 + 1;

    for (i = 1; i < count - 1; i++) {
        insertion_sort(A, (i - 1) * 5, i * 5 - 1);
    }
    insertion_sort(A, (count - 1) * 5, sizeof(A));

    if (count == 1) {
        return A[5 / 2 + 1];
    }

    B = (int *)malloc(sizeof(int) * count);
    for (i = 0; i < count - 1; i++0)
        B[i] = A[i * 5 + 3];
    B[i] = A[(count - 1) * 5 + (sizeof(A) - (count - 1) * 5 / 2)];

    x = select(B, 0, count - 1, count / 2);

    q = partition_x(A, p, r, x);
    k = q - p + 1;

    if (i == k)
        return x;
    else if (i < k)
        return select(A, p, q - 1, i);
    else
        return select(A, q + 1, r, i - k);
}
