/*
 * =====================================================================================
 *
 *       Filename:  xmath.c
 *
 *    Description:
 *
 *        Version:  1.0
 *        Created:  Wednesday 22 August 2018 09:03:45  IST
 *       Revision:  1.1
 *       Compiler:  gcc
 *
 *         Author:  Jagdish Prajapati (JP), prajapatijagdish@gmail.com
 *        Company:  Emsoftronic
 *
 * =====================================================================================
 */

#include "xmath.h"
#include <stdio.h>

xint_t xadd(xint_t x, xint_t y)
{
    int i;
    unsigned char *p = (unsigned char *)&x;
    unsigned char *q = (unsigned char *)&y;
    unsigned char out[sizeof(xint_t)];
    unsigned short tout = 0;
    for (i = 0; i < sizeof(xint_t); i++) {
        tout += (unsigned short)p[i] + (unsigned short)q[i];
        out[i] = (unsigned char)(tout & 0xff);
        tout >>= 8;
    }
    return *((xint_t *)out);
}

xint_t xlshift(xint_t x, unsigned int y)
{
    int i;
    int n = y >> 3;
    int b = y % 8;
    xint_t tmp = {0};
    unsigned char *p = (unsigned char *)&x;
    unsigned char *q = (unsigned char *)&tmp;
    for (i = n; i < sizeof(xint_t); i++) {
        if (i != n ) q[i] |= p[i-n -1] >> (8 - b);
        q[i] |= p[i-n] << b;
    }

    return tmp;
}

xint_t xnegate(xint_t x) {
    int i;
    unsigned char *p = (unsigned char *)&x;
    xint_t tmp = {0};
    unsigned char *q = (unsigned char *)&tmp;
    q[0] = 1;
    for (i = 0; i < sizeof(xint_t); i++) p[i] = ~ p[i];
    x = xadd(x, tmp);
    return x;
}

int xcomp(xint_t x, xint_t y)
{
    int i;
    unsigned char *p = (unsigned char *)&x;
    unsigned char *q = (unsigned char *)&y;
    int sp = p[sizeof(xint_t)-1]>>7;
    int sq = q[sizeof(xint_t)-1]>>7;
    if (sp && !sq) return -1;
    else if (!sp && sq) return 1;
    else {
        for (i = sizeof(xint_t) - 1; i >= 0; i--) {
            if (p[i] < q[i])  return -1;
            else if (p[i] > q[i])  return 1;
        }
    }
    return 0;
}

xint_t xrshift(xint_t x, unsigned int y)
{

    int i;
    int n = y >> 3;
    int b = y % 8;
    xint_t tmp = {0};
    unsigned char *p = (unsigned char *)&x;
    unsigned char *q = (unsigned char *)&tmp;
    for (i = 0; i < (int)(sizeof(xint_t)-n); i++) {
        q[i] |= p[i + n] >>  b;
        if (i != sizeof(xint_t) - n - 1) q[i] |= p[i + n + 1] << (8 - b);
    }

    return tmp;
}

xint_t xmul(xint_t x, xint_t y)
{
    int i;
    unsigned char *p = (unsigned char *)&y;
    xint_t tmp = {0};
    for (i = (sizeof(xint_t) << 3) - 1; i >= 0; i--) {
        if ((p[(i>>3)] >> (i%8)) & 0x1) {
            tmp = xadd(xlshift(x, (unsigned int)i), tmp);
        }
    }

    return tmp;
}

inline xint_t xsetb(xint_t x, unsigned int y)
{
    int n = y >> 3;
    int b = y % 8;
    unsigned char *p = (unsigned char *)&x;
    if (n < sizeof(xint_t)) p[n] |= 1 << b;
    return x;
}

inline xint_t xclrb(xint_t x, unsigned int y)
{
    int n = y >> 3;
    int b = y % 8;
    unsigned char *p = (unsigned char *)&x;
    if (n < sizeof(xint_t)) p[n] &= ~(1 << b);
    return x;
}


xint_t x_not(xint_t x) {
    int i;
    unsigned char *p = (unsigned char *)&x;
    xint_t tmp = {0};
    unsigned char *q = (unsigned char *)&tmp;
    q[0] = 1;
    for (i = 0; i < sizeof(xint_t); i++) p[i] = ~ p[i];

    return x;
}

xint_t xdiv(xint_t x, xint_t y)
{
    int i;
    xint_t k, out = {0};
    xint_t tmp = {0};
    unsigned char *p = (unsigned char *)&x;
    unsigned char *q = (unsigned char *)&y;
    int sp = p[sizeof(xint_t)-1]>>7;
    int sq = q[sizeof(xint_t)-1]>>7;

    if (xcomp(x, out) == 0) return out;
    if (xcomp(y, out) == 0) return xclrb(x_not(out), (sizeof(xint_t)<<3) - 1);

    if (sp) x = xnegate(x);
    if (sq) y = xnegate(y);

    for (i = ((sizeof(xint_t) << 2) - 1); i >= 0; --i) {
            k = xadd(tmp,xlshift(y, i));
        if (xcomp(k, x) <= 0) {
            tmp = k; //xadd(tmp, xlshift(y, i));
            out = xsetb(out, i);
        }
    }

    return (sp != sq)? xnegate(out) : out;
}


xint_t xmod(xint_t x, xint_t y)
{
    int i;
    xint_t k, out = {0};
    xint_t tmp = {0};
    unsigned char *p = (unsigned char *)&x;
    unsigned char *q = (unsigned char *)&y;
    int sp = p[sizeof(xint_t)-1]>>7;
    int sq = q[sizeof(xint_t)-1]>>7;

    if (xcomp(x, out) == 0) return out;
    if (xcomp(y, out) == 0) return out;

    if (sp) x = xnegate(x);
    if (sq) y = xnegate(y);

    if (xcomp(x, y) < 0) return x;

    for (i = ((sizeof(xint_t) << 2) - 1); i >= 0; --i) {
            k = xadd(tmp,xlshift(y, i));
        if (xcomp(k, x) <= 0) {
            tmp = k; //xadd(tmp, xlshift(y, i));
            out = xadd(x, xnegate(k)); //xsetb(out, i);
        }
    }

    //return (sp != sq)? xnegate(out) : out;
    return out;
}

void xprintInt(xint_t n, unsigned int base)
{
    xint_t tmp = {0};
    unsigned char *p = (unsigned char *)&n;
    char buff[sizeof(xint_t)<<3];
    int sp = p[sizeof(xint_t)-1]>>7;
    int i = sizeof(buff)-1;
    xint_t rem = {0};
    xint_t xbase = {0};
    unsigned char *r= (unsigned char *)&rem;
    *r = (unsigned char)base;
    xbase = rem;

    if (base == 10) n = xnegate(n);
    buff[i--] = '\0';

    while(xcomp(n,tmp) != 0){
        rem = xmod(n, xbase);
        if (*r < 10) buff[i--] = *r + '0' ;
        else buff[i--] = *r - 10 + 'a' ;
        n = xdiv(n, xbase);
    }

    if (sp) buff[i] = '-';
    else i++;
    printf("%s", &buff[i]);
}
