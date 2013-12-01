/*
 * =====================================================================================
 *
 *       Filename:  linkedlist.c
 *
 *    Description:  
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

typedef struct elemt{
    struct elemt    *prev;
    struct elemt    *next;
    int     key;
}ELEM;

//typedef struct elemt    ELEM;

typedef struct {
    ELEM    *head;
}LIST;

void
list_init(LIST *L)
{
    L->head = (ELEM *)malloc(sizeof(ELEM));
    L->head->next = L->head;
    L->head->prev = L->head;
    L->head->key = NULL;
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
    for (elem = L.head; elem != NULL; elem = elem->next) {
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
    for (elem = L.head; elem != NULL; elem = elem->next) {
        printf("%d ", elem->key);
    } printf("\n");

    free(L.head);
}
