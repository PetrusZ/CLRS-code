/*
 * =====================================================================================
 *
 *       Filename:  counting_sort.c
 *
 *    Description:
 *
 *        Version:  1.0
 *        Created:  2013年11月02日 14时41分38秒
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

void
counting_sort(int *A, int *B, int k, int size)
{
    int     i, j;
    int     *C;

    C = (int *)malloc(k * sizeof(int));

    for (i = 0; i < k; i++)
        C[i] = 0;
    for (j = 0; j < size; j++)
        C[A[j]] = C[A[j]] + 1;
    //C[i] now contains the number of elements equal to i.
    for (i = 0; i < k; i++)
        C[i] = C[i] + C[i - 1];
    //C[i] now contains the number of elements less than or equal to i.
    for (j = size - 1; j >= 0; j--) {
        B[C[A[j]] - 1] = A[j];
        C[A[j]] = C[A[j]] - 1;
    }

    free(C);
}

void
counting_sort_easy(int *A, int max, int size)
{
    int i, j;
    int count[max + 1];

    for (i = 0; i < max + 1; i++) {
        count[i] = 0;
    }
    for (i = 0; i < size; i++) {
        count[A[i]]++;
    }
    for (i = 0; i < max + 1; i++) {
        while(count[i]--) {
            A[j++] = i;
        }
    }
}

int
main(void)
{
    int i;
    int A[8] = {2,5,3,0,2,3,0,3};
    int *B;

    B = (int *)malloc(sizeof(A));


    /* counting_sort(A, B, 6, 8); */
    counting_sort_easy(A, 5, 8);

    for (i = 0; i < 8; i++)
        printf("%d ", A[i]);
    printf("\n");

    free(B);

    return(0);
}
