/*
 * =====================================================================================
 *
 *       Filename:  test.c
 *
 *    Description:
 *
 *        Version:  1.0
 *        Created:  Wednesday 22 August 2018 11:24:52  IST
 *       Revision:  1.1
 *       Compiler:  gcc
 *
 *         Author:  Jagdish Prajapati (JP), prajapatijagdish@gmail.com
 *        Company:  Emsoftronic
 *
 * =====================================================================================
 */

#include <stdio.h>

#include "xmath.h"

int main(void)
{
    xint_t x, y, out;
    int *a = &x;
    int *b = &y;
    int *c = &out;
    while(1) {
        printf("Enter data (x and y ) : ");
        fflush(stdout);
        scanf(" %d %d", a, b);
        out = xadd(x, y);
        printf("%d + %d = %d\n", *a, *b, *c);
        out = xlshift(x, *b);
        printf("%d << %d = %d\n", *a, *b, *c);
        out = xmul(x, y);
        printf("%d * %d = %d\n", *a, *b, *c);
        printf("mul result using xprintInt : ");
        xprintInt(out, 10);
        printf("\ncmp(%d, %d) = %d\n", (int)*a, (int)*b, xcomp(x, y));
        out = xadd(x, xnegate(y));
        printf("%d - %d = %d\n", *a, *b, *c);
        out = xrshift(x, *b);
        printf("%d >> %d = %d\n", *a, *b, *c);
        out = xclrb(x, *b);
        printf("clearBit(%04x, %d) = %04x\n", *a, *b, *c);
        out = xsetb(out, *b);
        printf("setBit(%04x, %d) = %04x\n", *c, *b, *c);
        out = x_not(x);
        printf("not(%04x) = %04x\n", *a, *c);
        out = xdiv(x, y);
        printf("%d / %d = %d\n", *a, *b, *c);
        out = xmod(x, y);
        printf("%d %% %d = %d\n", *a, *b, *c);
    }
    return 0;
}
