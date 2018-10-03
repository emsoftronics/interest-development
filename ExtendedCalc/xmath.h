/*
 * =====================================================================================
 *
 *       Filename:  xmath.h
 *
 *    Description:
 *
 *        Version:  1.0
 *        Created:  Wednesday 22 August 2018 08:37:38  IST
 *       Revision:  1.1
 *       Compiler:  gcc
 *
 *         Author:  Jagdish Prajapati (JP), prajapatijagdish@gmail.com
 *        Company:  Emsoftronic
 *
 * =====================================================================================
 */

#ifndef __XMATH_H__
#define __XMATH_H__
#define EXTENDED_INT_SIZE   8

typedef struct {
    unsigned char data[EXTENDED_INT_SIZE];
} xint_t;



extern xint_t xadd(xint_t x, xint_t y);
extern xint_t xmul(xint_t x, xint_t y);
extern xint_t xlshift(xint_t x, unsigned int y);
extern xint_t xrshift(xint_t x, unsigned int y);
extern xint_t xnegate(xint_t x);
extern int xcomp(xint_t x, xint_t y);
extern xint_t xrshift(xint_t x, unsigned int y);
extern xint_t xdiv(xint_t x, xint_t y);
extern inline xint_t xsetb(xint_t x, unsigned int y);
extern inline xint_t xclrb(xint_t x, unsigned int y);
extern xint_t x_not(xint_t x);
extern xint_t xmod(xint_t x, xint_t y);
extern void xprintInt(xint_t n, unsigned int base);
#endif /* __XMATH_H__ */
