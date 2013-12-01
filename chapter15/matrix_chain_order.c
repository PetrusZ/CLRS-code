/*
 * =====================================================================================
 *
 *       Filename:  matrix_chain_order.c
 *
 *    Description:  动态规划法解矩阵链乘法问题
 *
 *        Version:  1.0
 *        Created:  2013年11月27日 15时45分25秒
 *       Compiler:  gcc
 *
 *         Author:  codeplayer, silencly07@gmail.com
 *      Copyright:  Copyright (c) 2013, codeplayer
 *
 * =====================================================================================
 */
#include <stdlib.h>
#include <stdio.h>

void
matrix_chain_order(int *p, int m[7][7], int s[7][7])
{
    /*
     * 计算最优代价
     */
    int     i, j, k, l, n, q;           //l为矩阵链长度

    n = sizeof(p) / sizeof(char) - 2;   //n为矩阵个数

    for (i = 1; i <= n; i++)            //计算矩阵链长度为1时的m
        m[i][i] = 0;
    for (l = 2; l <= n; l++) {          //循环计算矩阵链长度大于1时的m
        for (i = 1; i <= n - l + 1; i++) {
            j = i + l - 1;
            m[i][j] = 65535;
            for (k = i; k <= j - 1; k++) {      //遍历寻找最优切割点
                q = m[i][k] + m[k + 1][j] + p[i - 1] * p[k]* p[j];  //矩阵乘法公式
                if (q < m[i][j]) {
                    m[i][j] = q;
                    s[i][j] = k;
                }
            }
        }
    }
}

void
print_optimal_parens(int s[7][7], int i, int j)
{
    /*
     * 重构最优解
     */
    if (i == j)
        printf("A%d", i);
    else {
        printf("(");
        print_optimal_parens(s, i, s[i][j]);
        print_optimal_parens(s, s[i][j] + 1, j);
        printf(")");
    }
}

int
main(int argc, const char *argv[])
{
    int     p[7] = {30, 35, 15, 5, 10, 20, 25};
    int     m[7][7] = {0};
    int     s[7][7] = {0};
    int     i, j;

    matrix_chain_order(p, m, s);

    printf("table m:\n");
    for (i = 1; i < 7; i++) {
        for (j = 1; j < 7; j++)
            printf("%5d ", m[i][j]);
        printf("\n");
    }

    printf("\n矩阵链A1...A6所需的最少乘法次数为： %d\n", m[1][6]);

    printf("最优解为：");
    print_optimal_parens(s, 1, 6);
    printf("\n");

    return 0;
}
