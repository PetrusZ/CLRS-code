/*
 * =====================================================================================
 *
 *       Filename:  find_maximum_subarray.c
 *
 *    Description:  寻找最大子数组
 *
 *        Version:  1.0
 *        Created:  2013年10月29日 15时03分25秒
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  YOUR NAME (), 
 *   Organization:  
 *
 * =====================================================================================
 */
#include <stdlib.h>
#include <math.h>

#define MIN     -65535

struct maxsubarr {
    int max_left;
    int max_right;
    int max_sum;
};

struct maxsubarr
find_max_crossing_subarray(int *A, int low, int mid, int high)
{
    /*
     * 求解跨越中点的最大子数组函数
     */

    int             i, j, sum, left_sum, right_sum;
    int             max_left, max_right;
    struct maxsubarr   max;

    //left_sum = -(pow(2, sizeof(int) * 8));
    left_sum = MIN;
    sum = 0;
    for (i = mid; i>= low; i--) {
        sum = sum + A[i];
        if (sum > left_sum) {
            left_sum = sum;
            max.max_left = i;
        }
    }

    //right_sum = -(pow(2, sizeof(int) * 8));
    right_sum = MIN;
    sum = 0;
    for (j = mid + 1; j <= high; j++) {
        sum = sum + A[j];
        if (sum > right_sum) {
            right_sum = sum;
            max.max_right = j;
        }
    }

    max.max_sum = left_sum + right_sum;
    return(max);
}

struct maxsubarr
find_maximum_subarray(int *A, int low, int high)
{
    int                 mid;
    struct maxsubarr    left, right, cross;

    if (high == low) {      /* base case: only one element */
        cross.max_left = low;
        cross.max_right = high;
        cross.max_sum = A[low];
        return(cross);
    } else {
        mid = (low + high) / 2;
        left = find_maximum_subarray(A, low, mid);
        right = find_maximum_subarray(A, mid + 1, high);
        cross = find_max_crossing_subarray(A, low, mid, high);

        if (left.max_sum >= right.max_sum && left.max_sum >= cross.max_sum)
            return(left);
        else if (right.max_sum >= left.max_sum && right.max_sum >= cross.max_sum)
            return(right);
        else
            return(cross);
    }
}

int
main(void)
{
    int A[16] = {13, -3, -25, 20, -3, -16, -23, 18, 20, -7, 12, -5, -22, 15, -4, 7};

    struct maxsubarr   max_subarray;

    max_subarray = find_maximum_subarray(A, 0, 15);

    printf("left: %d, right: %d, maxsum: %d\n", max_subarray.max_left, max_subarray.max_right, max_subarray.max_sum);
}
