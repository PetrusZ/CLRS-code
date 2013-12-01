/*
 * =====================================================================================
 *
 *       Filename:  main.c
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  2013年10月25日 14时57分48秒
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  YOUR NAME (), 
 *   Organization:  
 *
 * =====================================================================================
 */

#include <stdio.h>
#include <math.h>

extern void insertion_sort(int *A);
extern void merge_sort(int *A, int p, int r);
extern void quicksort(int *A, int p, int r);
extern void rand_quicksort(int *A, int p, int r);
extern int rand_select(int *A, int p, int r, int i);

void 
printf_A(int *A)
{
    int     i = 0;

    for ( ; A[i] != NULL; i++) {
        printf("%3d ", A[i]);
        if ((i + 1) % 35 == 0)
            printf("\n");
    }
    printf("\n");
}

int 
main(void)
{
    int     *A; 
    int     i;

    if ((A = malloc(1000 * sizeof(int))) == NULL) {
        printf("malloc error\n");
        return(-1);
    }

    for (i = 0; i < 1000; i++) {
        A[i] = rand() % 1000 + 1;
    }

    //insertion_sort(A);
    //merge_sort(A, 0, 999);
    //quicksort(A, 0, 999);
    //rand_quicksort(A, 0, 999);

    printf("i = %d\n", rand_select(A, 0, 999, 999));

    quicksort(A, 0, 999);
    printf_A(A);

    free(A);
    return(0);
}
