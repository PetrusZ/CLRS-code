/*
 * =====================================================================================
 *
 *       Filename:  rand_in_place.c
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  2013年10月31日 11时34分15秒
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  YOUR NAME (), 
 *   Organization:  
 *
 * =====================================================================================
 */
#include <stdlib.h>

randomize_in_place(int *A, int n)
{
    int     i;
    int     temp;
    int     rand;

    for(i = 0;i < n; i++) {
        rand = random(i, n);
        temp = A[i];
        A[i] = A[rand];
        A[rand] = temp;
    }
}
