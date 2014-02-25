/*
* =====================================================================================
*
* Filename: cut_rod_dp.c
*
* Description: 钢条切割问题的动态规划算法
*
* Version: 1.0
* Created: 2013年11月26日 17时08分15秒
* Compiler: gcc
*
* Author: codeplayer, silencly07@gmail.com
* Copyright: Copyright (c) 2013, codeplayer
*
* =====================================================================================
*/
#include <stdlib.h>
#include <stdio.h>

#define MAX(a, b) ((a) > (b) ? (a) : (b))

int
memized_cut_rod_aux(int *p, int n, int *r)
{
    int i, q;

    if (r[n - 1] >= 0)
        return(r[n - 1]);
    if (n == 1)
        q = 0;
    else {
        q = -65535;
        for (i = 1; i < n; i++) {
            q = MAX(q, p[i] + memized_cut_rod_aux(p, n - i, r));
        }
    }

    r[n - 1] = q;

    return(q);
}

int
memized_cut_rod(int *p, int n)
{
    int i, *r, max;

    r = (int *)malloc(n * sizeof(int));

    for (i = 0; i < n; i++) {
        r[i] = -65535;
    }

    max = memized_cut_rod_aux(p, n, r);

    free(r);

    return(max);
}

int
bottom_up_cut_rod(int *p, int n)
{
    int i, j, q;
    int r[n];
    r[0] = 0;

    for (j = 1; j < n; j++) {
        q = -65535;

        for (i = 1; i <= j; i++)
            q = MAX(q, p[i] + r[j - i]);

        r[j] = q;
    }

    return(r[n - 1]);
}

int
extended_bottom_up_cut_rod(int *p, int n, int *r, int *s)
{
    int i, j ,q;

    r[0] = 0;
    for (j = 1; j < n; j++) {
        q = -65535;

        for (i = 1; i <= j; i++) {
            if (q < p[i] + r[j - i]) {
                q = p[i] + r[j - i];
                s[j] = i;
            }
        }
        r[j] = q;
    }
    return 1;
}

void
print_cut_rod_solution(int *p, int n)
{
    int r[n], s[n];

    extended_bottom_up_cut_rod(p, n, r, s);

    while (n - 1 > 0) {
        printf("%d ", s[n - 1]);
        n = n - s[n - 1];
    }
    printf("\n");
}

int
main(int argc, const char *argv[])
{
    int p[11] = {0, 1, 5, 8, 9, 10, 17, 17, 20, 24, 30};
    /* int max; */

    /* max = memized_cut_rod(p, 11); */
    /* max = bottom_up_cut_rod(p, 11); */
    /* printf("%d\n", max); */

    print_cut_rod_solution(p, 8);

    return 0;
}
