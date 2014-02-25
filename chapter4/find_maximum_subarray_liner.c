/*
 * =====================================================================================
 *
 *       Filename:  find_maximum_subarray_liner.c
 *
 *    Description:  寻找最大子数组问题（线性时间）（似乎是贪心算法）
 *
 *        Version:  1.0
 *        Created:  2013年10月29日 17时35分14秒
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

int find_maximum_subarray_liner(const int A[],int n)
{
    int thisum, maxsum, i;

    thisum = maxsum = 0;

    for(i = 0; i < n; i++) {
        thisum += A[i];
        if(thisum > maxsum)
            maxsum = thisum;
        else if(thisum < 0)
            thisum = 0;
    }
    return maxsum;
}

int
main(void)
{
    int A[16] = {13, -3, -25, 20, -3, -16, -23, 18, 20, -7, 12, -5, -22, 15, -4, 7};
    int maxsubarr;

    maxsubarr = find_maximum_subarray_liner(A, 16);

    printf("maxsubarray: %d\n", maxsubarr);
}

