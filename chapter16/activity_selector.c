/*
 * =====================================================================================
 *
 *       Filename:  activity_selector.c
 *
 *    Description:  贪心算法求解活动选择问题
 *
 *        Version:  1.0
 *        Created:  2013年11月29日 18时57分18秒
 *       Compiler:  gcc
 *
 *         Author:  codeplayer, silencly07@gmail.com
 *      Copyright:  Copyright (c) 2013, codeplayer
 *
 * =====================================================================================
 */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define N       11
#define MAXBUF  20

void
recursive_activity_selector(int *s, int *f, int k, int n , char *a)
{
    int     m;
    char    buf[4];

    m = k + 1;
    while (m <= n && s[m] < f[k])
        /*
         * 跳过开始时间在f[k]之前的活动
         */
        m = m + 1;
    if (m <= n) {
        /*
         * 贪心选择，找到开始时间在f[k]之后的第一个活动后，
         * 直接把它加入到活动列表中
         */
        sprintf(buf, "a%d ", m);
        strcat(a, buf);
        recursive_activity_selector(s, f, m, n, a);
    }
}

void
greedy_activity_selector(int *s, int *f, char *a)
{
    int     k, n, m;
    char    buf[4];

    strcat(a, "a1 ");
    n = N;
    k = 1;

    for (m = 2; m <= n; m++) {
        if (s[m] >= f[k]) {
            sprintf(buf, "a%d ", m);
            strcat(a, buf);
            k = m;
        }
    }
}

int
main(int argc, const char *argv[])
{
    int     s[N + 1] = {0, 1, 3, 0, 5, 3, 5,  6,  8,  8,  2, 12};
    int     f[N + 1] = {0, 4, 5, 6, 7, 9, 9, 10, 11, 12, 14, 16};
    char    a[MAXBUF] = "";

    /* recursive_activity_selector(s, f, 0, N, a); */
    greedy_activity_selector(s, f, a);

    printf("%s", a);

    return 0;
}
