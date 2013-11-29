/*
 * =====================================================================================
 *
 *       Filename:  optimal_bst.c
 *
 *    Description:  动态规划的方法求解最优二叉搜索树
 *
 *        Version:  1.0
 *        Created:  2013年11月28日 21时19分51秒
 *       Compiler:  gcc
 *
 *         Author:  codeplayer, silencly07@gmail.com
 *      Copyright:  Copyright (c) 2013, codeplayer
 *
 * =====================================================================================
 */
#include <stdlib.h>
#include <stdio.h>

#define N           5
#define INFINITY    65535

void
optimal_bst(float *p, float *q, int n, float (*e)[N + 1], int (*root)[N + 1])
{
    int     i, j, l, r;
    float   t;
    float   w[N + 2][N + 1] = {0};

    for (i = 1; i <= n + 1; i++) {  /* 根据公式15.14和15.15，以概率q[i-1]初始化表e和w中的空子树 */
        e[i][i - 1] = q[i - 1];
        w[i][i - 1] = q[i - 1];
    }
    for (l = 1; l <= n; l++) {      /* 与矩阵链相乘问题类似，自底向上遍历所有可能的最优BST */
        for (i = 1; i <= n - l + 1; i++) {
            j = i + l - 1;
            e[i][j] = INFINITY;
            w[i][j] = w[i][j - 1] + p[j] + q[j];    /* 公式15.15 */

            for (r = i; r <= j; r++) {  /* 遍历所有可能确定最优子树根 */
                t = e[i][r - 1] + e[r + 1][j] + w[i][j];    /* 公式15.14 */
                if (t < e[i][j]) {
                    e[i][j] = t;
                    root[i][j] = r;
                }
            }
        }
    }
}

void
construct_optimal_bst(int (*root)[N + 1], int i, int j)
{
    int     r;

    if (i == 1 && j == N) {
        printf("k%d为根\n", root[1][N]);
    }
    if (i < j) {
        r = root[i][j];

        if (r != i)
            printf("k%d为k%d的左孩子\n", root[i][r - 1], r);
        construct_optimal_bst(root, i, r - 1);
        if (r != j)
            printf("k%d为k%d的右孩子\n", root[r + 1][j], r);
        construct_optimal_bst(root, r + 1, j);
    }

    if (i == j) {
        printf("d%d为k%d的左孩子\n", i - 1, i);
        printf("d%d为k%d的右孩子\n", i, i);
    }

    if (i > j) {
        printf("d%d为k%d的右孩子\n", j, j);
    }
}

int
main(int argc, const char *argv[])
{
    float   p[N + 1] = {0, 0.15, 0.10, 0.05, 0.10, 0.20};
    float   q[N + 1] = {0.05, 0.10, 0.05, 0.05, 0.05, 0.10};
    float   e[N + 2][N + 1] = {0};
    int     root[N + 1][N + 1] = {0};

    optimal_bst(p, q, N, e, root);

    construct_optimal_bst(root, 1, N);

    return 0;
}
