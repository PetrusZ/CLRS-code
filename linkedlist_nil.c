/*
 * =====================================================================================
 *
 *       Filename:  linkedlist.c
 *
 *    Description:  有哨兵的双向循环链表
 *
 *        Version:  1.0
 *        Created:  2013年11月04日 16时15分47秒
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

struct elemt{
    struct elemt    *prev;
    struct elemt    *next;
    int     key;
};

typedef struct elemt    ELEM;

typedef struct {
    ELEM    *nil;
}LIST;

void
list_init(LIST *L)
{
    L->nil = (ELEM *)malloc(sizeof(ELEM));
    L->nil->next = L->nil;
    L->nil->prev = L->nil;
    L->nil->key = NULL;
}

void
list_insert(LIST *L, int key)
{
    ELEM    *x;

    x = (ELEM *)malloc(sizeof(ELEM));
    x->key = key;
    x->next = L->nil->next;
    L->nil->next->prev = x;
    L->nil->next = x;
    x->prev = L->nil;
}

void
list_delete(LIST *L, ELEM *x)
{
    x->prev->next = x->next;
    x->next->prev = x->prev;
    free(x);
}

ELEM *
list_search(LIST *L, int k)
{
    ELEM    *x;

    x = L->nil->next;
    while (x != L->nil && x->key != k) {
        x = x->next;
    }

    if (x->key != k)
        x = NULL;

    return(x);
}

int
main(void)
{
    LIST    L;
    ELEM    *elem;

    list_init(&L);
    list_insert(&L, 29);
    list_insert(&L, 48);
    list_insert(&L, 93);
    list_insert(&L, 38);
    list_insert(&L, 12);
    list_insert(&L, 94);

    printf("after insert: ");
    for (elem = L.nil->next; elem != L.nil; elem = elem->next) {
        printf("%d ", elem->key);
    }
    printf("\n");

    elem = list_search(&L, 12);
    list_delete(&L, elem);
    elem = list_search(&L, 93);
    list_delete(&L, elem);
    elem = list_search(&L, 29);
    list_delete(&L, elem);

    printf("after delete: ");
    for (elem = L.nil->next; elem != L.nil; elem = elem->next) {
        printf("%d ", elem->key);
    }
    printf("\n");

    free(L.nil);

}
