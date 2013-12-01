/*
 * =====================================================================================
 *
 *       Filename:  radixsort_CLRS.c
 *
 *    Description:
 *
 *        Version:  1.0
 *        Created:  2013年11月03日 14时20分27秒
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  YOUR NAME (),
 *   Organization:
 *
 * =====================================================================================
 */
#include <stdlib.h>
/*被排序元素的最大位数，4则意味着只能排序< 10000 的数*/
#define WIDTH 4
#define MAXK 10  //位数划分基于的基数，10表示为10进制划分

void radixSort(int a[], int n) {
	int i;
	void innerCountingSort(int a[], int n, int d);
	for (i = 0; i < WIDTH; i++) {
		innerCountingSort(a, n, i);
	}
}

void innerCountingSort(int a[], int n, int d) {
	int i, j, x, k[MAXK] = {0};
	int *ip = (int *)malloc(n * sizeof(int));
	int *bp = (int *)malloc(n * sizeof(int));
	int getDValue(int value, int d);
	for (i = 0; i < n; i++) {
		ip[i] = getDValue(a[i], d);
		k[ip[i]]++;
	}

	for (j = 1; j < MAXK; j++) {
		k[j] = k[j] + k[j-1];
	}

	for (i = n - 1; i >= 0; i--) {
		bp[k[ip[i]] - 1] = a[i];
		k[ip[i]]--;
	}

	for (i = 0; i < n; i++) {
		a[i] = bp[i];
	}

	free(ip);
	free(bp);
}

/*
*获取一个数第d位数的值，位数索引从0开始
*/
int getDValue(int value, int d) {
	for (;d > 0 && value > 0; d--) {
		value = value / MAXK;
	}
	return value % MAXK;
}

int main(int argc, char *argv[])
{
    int i;
    int array[30] = {258, 976, 515, 337, 359, 701, 916, 494, 303, 175,
                        677, 825, 131, 560, 147, 254, 759, 814, 917, 382,
                        452, 114, 873, 585, 881, 127, 819, 658, 461, 435};

    printf("before\n");
    for (i=0; i<30; i++)
        printf("%d  ", array[i]);
    printf("\n");

    /* 排序函数，从个位开始 */
    radixSort(array, 30);

    printf("final\n");
    for (i=0; i<30; i++)
        printf("%d  ", array[i]);
    printf("\n");

    return 0;
}
