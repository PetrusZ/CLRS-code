/*
 * =====================================================================================
 *
 *       Filename:  stack.c
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  2013年11月04日 11时34分41秒
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

struct stack {
    int     *stack;
    int     size;
    int     top;
};

void
stack_init(struct stack *S)
{
    S->size = 100;
    S->stack = (int *)malloc(sizeof(int) * S->size);
    S->top = -1;
}

int
stack_empty(struct stack *S)
{
    if (S->top == -1)
        return 1;
    else
        return 0;
}

void
push(struct stack *S, int x)
{
    if (S->top == S->size) {
        printf("error: up to overflow\n");
    } else {
        S->top++;
        S->stack[S->top] = x;
    }
}

pop(struct stack *S)
{
    if (stack_empty(S)) {
        printf("error: stack underflow\n");
    } else {
        S->top--;
        return(S->stack[S->top + 1]);
    }
}

int
main(void)
{
    int             i;
    struct stack    S;

    stack_init(&S);
    push(&S, 10);
    push(&S, 1);
    push(&S, 32);
    push(&S, 83);
    push(&S, 23);

    printf("after push: ");
    for (i = 0; i <= S.top; i++) {
        printf("%d ", S.stack[i]);
    }
    printf("\n");

    pop(&S);
    pop(&S);
    pop(&S);
    printf("after pop: ");
    for (i = 0; i <= S.top; i++) {
        printf("%d ", S.stack[i]);
    }
    printf("\n");

    return(0);
}
