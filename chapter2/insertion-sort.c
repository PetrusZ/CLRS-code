/*
 * =====================================================================================
 *
 *       Filename:  insertion-sort.c
 *
 *    Description:
 *
 *        Version:  1.0
 *        Created:  2013年10月25日 14时51分15秒
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  YOUR NAME (),
 *   Organization:
 *
 * =====================================================================================
 */
void
insertion_sort(int  *A)
{
    int     i, j;
    int     key;

    for (j = 1; A[j] != 0; j++) {
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
