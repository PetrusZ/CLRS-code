/*
 * =====================================================================================
 *
 *       Filename:  find_min_max.c
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  2013年11月03日 16时57分24秒
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  YOUR NAME (), 
 *   Organization:  
 *
 * =====================================================================================
 */
#include <stdlib.h>

void
find_min_max(int *A, int *min, int *max)
{

    *min = 65535;
    *max = 0;

    int i;
    for (i = 0; i < sizeof(A); i = i + 2) {
        if (i + 1 <= sizeof(A)) {
            if (A[i] < A[i + 1]) {
                if (A[i] < *min)
                    *min = A[i];
                if (A[i + 1] > *max)
                    *max = A[i + 1];
            } else {
                if (A[i + 1] < *min)
                    *min = A[i + 1];
                if (A[i] > *max)
                    *max = A[i];
            }
        }
    }

}

int
main(void)
{
    int min, max;

    int A[] = {1,3,5,7,98,3,3,12,3,54};

    find_min_max(A, &min, &max);

    printf("min = %d, max = %d\n", min, max);
}
