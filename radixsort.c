/*
 * =====================================================================================
 *
 *       Filename:  radixsort.c
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  2013年11月02日 15时48分03秒
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
#include <string.h>
 
/* 获取输入数字的索引值，dec指定数字的位数，3代表百位数，order指定需要获取哪一位的索引，1代表个位，2代表十位，3代表百位 */
int get_index(int num, int dec, int order)
{
    int i, j, n;
    int index;
    int div;
 
    /* 根据位数，循环减去不需要的高位数字 */
    for (i=dec; i>order; i--) {
        n = 1;
        for (j=0; j<dec-1; j++)
            n *= 10;
        div = num/n;
        num -= div * n;
        dec--;
    }
 
    /* 获得对应位数的整数 */
    n = 1;
    for (i=0; i<order-1; i++)
        n *= 10;
 
    /* 获取index */
    index = num / n;
 
    return index;
}
 
/* 进行基数排序 */
void radix_sort(int array[], int len, int dec, int order)
{
    int i, j;
    int index;     /* 排序索引 */
    int tmp[len];  /* 临时数组，用来保存待排序的中间结果 */
    int num[10];   /* 保存索引值的数组 */
    memset(num, 0, 10*sizeof(int));  /* 数组初始清零 */
    memset(tmp, 0, len*sizeof(int)); /* 数组初始清零 */
 
    if (dec < order) /* 最高位排序完成后返回 */
        return;
 
    for (i=0; i<len; i++) {
        index = get_index(array[i], dec, order);  /* 获取索引值 */
        num[index]++;  /* 对应位加一 */
    }
 
    for (i=1; i<10; i++)
        num[i] += num[i-1]; /* 调整索引数组 */
 
    for (i=len-1; i>=0; i--) {
        index = get_index(array[i], dec, order);  /* 从数组尾开始依次获得各个数字的索引 */
        j = --num[index];  /* 根据索引计算该数字在按位排序之后在数组中的位置 */
        tmp[j] = array[i]; /* 数字放入临时数组 */
    }
 
    for (i=0; i<len; i++)
        array[i] = tmp[i];  /* 从临时数组复制到原数组 */
 
    printf("the %d time\n", order);
    for (i=0; i<30; i++)
        printf("%d  ", array[i]);
    printf("\n");
 
    /* 继续按高一位的数字大小进行排序 */
    radix_sort(array, len, dec, order+1);
 
    return;
}
 
int main(int argc, char *argv[])
{
    int i;
    int array[30] = {258, 976, 515, 337, 359, 701, 916, 494, 303, 175,
                        677, 825, 131, 560, 147, 254, 759, 814, 917, 382,
                        452, 114, 873, 585, 881, 127, 819, 658, 461, 435};
 
    int len = 30;  /* 测试数据个数 */
    int dec = 3;   /* 数据位数，3代表3位数 */
    int order = 1; /* 排序的位数，1代表个位、2代表十位、3代表百位 */
 
    printf("before\n");
    for (i=0; i<30; i++)
        printf("%d  ", array[i]);
    printf("\n");
 
    /* 排序函数，从个位开始 */
    radix_sort(array, len, dec, order);
 
    printf("final\n");
    for (i=0; i<30; i++)
        printf("%d  ", array[i]);
    printf("\n");
 
    return 0;
}
