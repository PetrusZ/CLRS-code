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
counting_sort(int *A, int *B, int k)
{
    int     i, j;
    int     *C;

    C = (int *)malloc(k * sizeof(int));

    for (i = 0; i < k; i++)
        C[i] = 0;
    for (j = 0; j < sizeof(A)/sizeof(char); j++)
        C[A[j]] = C[A[j]] + 1;
    //C[i] now contains the number of elements equal to i.
    for (i = 0; i < k; i++)
        C[i] = C[i] + C[i - 1];
    //C[i] now contains the number of elements less than or equal to i.
    for (j = sizeof(A)/sizeof(char) - 1; j >= 0; j--) {
        B[C[A[j]] - 1] = A[j];
        C[A[j]] = C[A[j]] - 1;
    }

    free(C);
}

int
main(void)
{
    int i;
    int A[8] = {2,5,3,0,2,3,0,3};
    int *B;

    B = (int *)malloc(sizeof(A));


    counting_sort(A, B, 6);

    for (i = 0; i < 8; i++)
        printf("%d ", B[i]);
    printf("\n");

    free(B);
    
    return(0);
}
