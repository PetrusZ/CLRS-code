/*
 * =====================================================================================
 *
 *       Filename:  cut_rod.c
 *
 *    Description:  递归求解钢铁切割问题
 *
 *        Version:  1.0
 *        Created:  2013年11月26日 14时53分04秒
 *       Compiler:  gcc
 *
 *         Author:  codeplayer, silencly07@gmail.com
 *      Copyright:  Copyright (c) 2013, codeplayer
 *
 * =====================================================================================
 */
#include <stdlib.h>
#include <stdio.h>

#define MAX(a, b)   ((a) > (b) ? (a) : (b))

int
cut_rod(int *p, int n)
{
    int     i, q;

    if (n == 1)
        return(0);
    q = -65535;
    for (i = 1; i < n; i++) {
        q = MAX(q, p[i] + cut_rod(p, n - i));
    }

    return(q);
}

int
main(int argc, const char *argv[])
{
    int     p[11] = {0, 1, 5, 8, 9, 10, 17, 17, 20, 24, 30};
    int     max;

    max = cut_rod(p, 11);

    printf("%d\n", max);

    return 0;
}
