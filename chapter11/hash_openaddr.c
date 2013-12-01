/*
 * =====================================================================================
 *
 *       Filename:  hash_openaddr.c
 *
 *    Description:  散列表开放寻址法的实现
 *
 *        Version:  1.0
 *        Created:  2013年11月07日 20时21分35秒
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

#define m           17
//#define HASH(k)    k % m       //除法散列法

#define A           0.85
//#define HASH(k)    (int)(m * (k * A - (int)(k * A)))         //乘法散列法

#define c1          7
#define c2          5
//#define h(k, i)     (HASH(k) + i) % m       //线性探查
//#define h(k, i)     (HASH(i) + c1 * i + c2 * i * i) % m         //二次探查

#define h1(k)       k % m
#define h2(k)       1 + (k % (m - 1))
#define h(k, i)     (h1(k) + i * h2(k)) % m       //双重散列

#define DEL         -65535

int
hash_insert(int *T, int k)
{
    /*
     * 在散列表中插入一个元素，不断的探查
     * 以找到一个空槽可以插入，或者探查了
     * 整个散列表，输出错误信息并退出
     */
    int     i, j;
    
    for (i = 0; i != m; i++) {
        j = h(k, i);
        if (T[j] == NULL || T[j] == DEL) {
            T[j] = k;
            return(j);
        }
    }

    fprintf(stderr, "hash table overflow\n");
    exit(1);
}

int
hash_search(int *T, int k)
{
    /*
     * 在散列表中查找一个元素，不断进行
     * 探查，直到找到该元素，或者探查到
     * 了一个空槽，或者找遍了整个散列表
     */
    int     i, j;

    for (i = 0; i != m; i++) {
        j = h(k, i);
        if (T[j] == k) {
            printf("found value: %d in key: %d\n", k, j);
            return(j);
        } else if (T[j] == NULL) {
            break;
        }
    }

    fprintf(stderr, "can't find value: %d\n", k);
    return(NULL);
}

int
hash_delete(int *T, int k)
{
    /*
     * 删除一个元素的时候并不将它置为NULL，
     * 因为这有可能会使得在查找的时候找不到
     * 后续的元素，查找在删除的地方就中断了。
     * 可以在删除的时候将其置为一个特殊的值，
     * 以避免这种情况。这里用的是DEL。
     */
    int     i, j;

    for (i = 0; i != m; i++) {
        j = h(k, i);
        if (T[j] == k) {
            T[j] = DEL;
            return(0);
        }
    }

    fprintf(stderr, "can't find %d in hashtable\n", k);
    exit(1);
}

void
print_hash(int *T)
{
    int     i;

    printf("---------------hashtable---------------\n");
    for (i = 0; i < m; i++) {
        if (T[i] != NULL && T[i] != DEL)
            printf("key: %2d, value: %4d\n", i, T[i]);
        else
            printf("key: %2d, value: NULL\n", i);
    }
    printf("------------------end------------------\n\n");
}

int
main(void)
{
    /*
     * 用数组实现的简单的开放寻址法的散列表
     */
    int     i;
    int     T[m];

    for (i = 0; i < m; i++) {
        T[i] = NULL;
    }

    hash_insert(T, 28);
    hash_insert(T, 438);
    hash_insert(T, 923);
    hash_insert(T, 239);
    hash_insert(T, 29);
    hash_insert(T, 31);
    hash_insert(T, 32);
    hash_insert(T, 39);
    hash_insert(T, 2);
    hash_insert(T, 24);
    hash_insert(T, 432);

    print_hash(T);

    hash_delete(T, 239);
    hash_delete(T, 31);
    hash_delete(T, 28);

    printf("\nafter delete 239, 31, 28...\n\n");

    print_hash(T);

    hash_search(T, 438);
    hash_search(T, 239);

    exit(0);
}
