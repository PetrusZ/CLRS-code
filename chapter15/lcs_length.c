/*
 * =====================================================================================
 *
 *       Filename:  lcs_length.c
 *
 *    Description:  动态规划法解最长公共子序列问题
 *
 *        Version:  1.0
 *        Created:  2013年11月28日 14时39分37秒
 *       Compiler:  gcc
 *
 *         Author:  codeplayer, silencly07@gmail.com
 *      Copyright:  Copyright (c) 2013, codeplayer
 *
 * =====================================================================================
 */
#include <stdlib.h>
#include <stdio.h>

/* DNA串 例1 */
#define A   1
#define C   2
#define G   3
#define T   4

/* 简单的ABCD 例2 */
/* #define A   1 */
/* #define B   2 */
/* #define C   3 */
/* #define D   4 */

#define UPRIGTH     5
#define UP          6
#define LEFT        7

/* 例1 */
#define XLEN       29
#define YLEN       28

/* 例2 */
/* #define XLEN       7 */
/* #define YLEN       6 */

void
lcs_length(int *x, int *y, int c[XLEN + 1][YLEN + 1], int b[XLEN + 1][YLEN + 1])
{
    int     i, j;

    for (i = 0; i <= XLEN; i++)
        c[i][0] = 0;
    for (j = 0; j <= XLEN; j++)
        c[0][j] = 0;

    for (i = 1; i <= XLEN; i++)
        for (j = 1; j <= YLEN; j++) {
            if (x[i] == y[j]) {
                c[i][j] = c[i - 1][j - 1] + 1;
                b[i][j] = UPRIGTH;
            } else if (c[i -1][j] >= c[i][j - 1]) {
                c[i][j] = c[i - 1][j];
                b[i][j] = UP;
            } else {
                c[i][j] = c[i][j - 1];
                b[i][j] = LEFT;
            }
        }
}

void
print_elem(int x)
{
    switch(x) {
        case A:
            printf("A");
            break;
        /* case B: */
            /* printf("B"); */
            /* break; */
        case C:
            printf("C");
            break;
        /* case D: */
            /* printf("D"); */
            /* break; */
        case G:
            printf("G");
            break;
        case T:
            printf("T");
            break;
        default:
            printf("0");
    }
}

void
print_arrow(int x)
{
    switch(x) {
        case UPRIGTH:
            printf("↖ ");
            break;
        case UP:
            printf("↑ ");
            break;
        case LEFT:
            printf("← ");
            break;
        default:
            printf("0 ");
    }
}

int
print_lcs(int b[XLEN + 1][YLEN + 1], int *x, int i, int j)
{
    if (i == 0 || j == 0)
        return(0);
    if (b[i][j] == UPRIGTH) {
        print_lcs(b, x, i -1, j - 1);
        print_elem(x[i]);
    } else if (b[i][j] == UP) {
        print_lcs(b, x, i - 1, j);
    } else {
        print_lcs(b, x, i, j - 1);
    }
}

int
main(void)
{
    int     n, m;
    int     i, j;
    /* 例1 */
    int     x[XLEN + 1] = {0,A,C,C,G,G,T,C,G,A,G,T,G,C,G,C,G,G,A,A,G,C,C,G,G,C,C,G,A,A};
    int     y[YLEN + 1] = {0,G,T,C,G,T,T,C,G,G,A,A,T,G,C,C,G,T,T,G,C,T,C,T,G,T,A,A,A};
    /* 例2 */
    /* int     x[XLEN + 1] = {0, A, B, C, B, D, A, B}; */
    /* int     y[YLEN + 1] = {0, B, D, C, A, B, A}; */

    int     c[XLEN + 1][YLEN + 1] = {0};
    int     b[XLEN + 1][YLEN + 1] = {0};

    lcs_length(x, y, c, b);

    printf("table b:\n");
    for (i = 0; i <= XLEN; i++) {
        for (j = 0; j <= YLEN; j++) {
            print_arrow(b[i][j]);
        }
        printf("\n");
    }
    printf("\n");

    printf("table c:\n");
    for (i = 0; i <= XLEN; i++) {
        for (j = 0; j <= YLEN; j++)
            printf("%2d ", c[i][j]);
        printf("\n");
    }
    printf("\n");

    printf("sequence X: ");
    for (i = 1; i <= XLEN; i++)
        print_elem(x[i]);
    printf("\n");
    printf("sequence Y: ");
    for (i = 1; i <= YLEN; i++)
        print_elem(y[i]);
    printf("\n");

    printf("LCS: ");
    print_lcs(b, x, XLEN, YLEN);

    return 0;
}
