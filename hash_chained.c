/*
 * =====================================================================================
 *
 *       Filename:  hash.c
 *
 *    Description:  散列表的链接法实现
 *
 *        Version:  1.0
 *        Created:  2013年11月06日 13时31分52秒
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

#define m           16
//#define HASH(k)     k % m         //除法散列法

#define A           0.65
#define HASH(k)     (int)(m * (k * A - (int)(k * A)))         //乘法散列法

int
HASH_(int k)
{
    /*
     * 全域散列函数（待完善）
     */
    int p = 1713;
    int a = rand() % (p - 1) + 1;
    int b = rand() % p;

    return(((a * k + b) % p) % m);
}

struct elemt{
    struct elemt    *prev;
    struct elemt    *next;
    int     key;
};

typedef struct elemt    ELEM;

typedef struct {
    ELEM    *head;
}LIST;

void
list_init(LIST *L)
{
    L->head = (ELEM *)malloc(sizeof(ELEM));
    L->head->next = L->head;
    L->head->prev = L->head;
    L->head->key = 0;
}

void
list_insert(LIST *L, int key)
{
    /*
     * 给定一个关键字key，将key插入到链表的最前端。
     */
    ELEM    *x;

    x = (ELEM *)malloc(sizeof(ELEM));
    x->key = key;
    if (L->head->next == L->head && L->head->prev == L->head)
        x->next = NULL;
    else
        x->next = L->head;
    if (L->head->next != L->head) {
        L->head->prev = x;      //L->head->prev表示的是L->head所指向的对象的prev属性
    }
    L->head = x;
    x->prev = NULL;
}

void
list_delete(LIST *L, ELEM *x)
{
    /*
     * 给定需要删除的元素x，通过修改指针将x从链表中删除。
     */
    if (x->prev != NULL) {
        x->prev->next = x->next;
    } else {
        L->head = x->next;
    }

    if (x->next != NULL) {
        x->next->prev = x->prev;
    }

    free(x);
}

ELEM *
list_search(LIST *L, int k)
{
    /*
     * 给定关键字k，查找链表中第一个关键字为k的元素，并返回指向该元素的指针。
     */
    ELEM    *x;

    x = L->head;
    while (x != NULL && x->next != x && x->key != k) {
        x = x->next;
    }

    if (x == NULL || x->key != k)
        x = NULL;

    return(x);
}

void
hash_insert(LIST *table, int x)
{
    /*
     * 将元素x散列后，调用链表的插入以将x到散列表中
     */
    list_insert(&table[HASH(x)], x);
}

void
hash_delete(LIST *table, int x)
{
    /*
     * 调用链表搜索找到元素x的，然后再调用链表删除
     * 将其从散列表中删除
     */
    ELEM    *k;

    k = list_search(&table[HASH(x)], x);
    list_delete(&table[HASH(x)], k);
}

void
hash_search(LIST *table, int x)
{
    /*
     * 为了方便测试，将散列表的搜索做了一点修改，
     * 直接在stdout中输出是否找到了该元素。
     */
    ELEM    *k;
    k = list_search(&table[HASH(x)], x);
    /*
    if (k != NULL)
        return(k->key);
    else
        return(NULL);
    */

    if (k != NULL)
        printf("found %d, key = %d\n", x, HASH(x));
    else
        fprintf(stderr, "can't found %d\n", x);
}

void
print_hash(LIST *table)
{
    /*
     * 打印散列表
     */
    int     i;
    ELEM    *j;

    printf("--------------HASHTABLE--------------\n");
    for (i = 0; i < m; i++) {
        printf("key = %2d: ", i);
        j = table[i].head;
        if (j != NULL && j->next != table[i].head)
            for ( ; j != NULL; j = j->next) {
                printf("value = %4d  ", j->key);
            }
        else
            printf("value = NULL  ", i);

        printf("\n");
    }
    printf("-----------------END-----------------\n");
}

int
main(void)
{
    /*
     * 简单的使用链表数组实现散列表
     */
    int     i, key;
    LIST    table[m];

    for (i = 0; i < m; i++) {
        list_init(&table[i]);
    }

    hash_insert(table, 38);
    hash_insert(table, 123);
    hash_insert(table, 94);
    hash_insert(table, 29);
    hash_insert(table, 48);
    hash_insert(table, 38);
    hash_insert(table, 923);
    hash_insert(table, 31);
    hash_insert(table, 32);
    hash_insert(table, 39);
    hash_insert(table, 2);
    hash_insert(table, 24);
    hash_insert(table, 823);

    print_hash(table);

    hash_delete(table, 38);
    hash_delete(table, 48);
    hash_delete(table, 31);

    printf("\nafter delete 38, 48, 31:\n\n");

    print_hash(table);

    printf("\nsearch 923: \n\n");
    hash_search(table, 923);

    printf("\nsearch 239: \n\n");
    hash_search(table, 239);

    exit(0);
}
