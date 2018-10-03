/*
 * =====================================================================================
 *
 *       Filename:  test_main.c
 *
 *    Description:
 *
 *        Version:  1.0
 *        Created:  Friday 26 May 2017 10:33:46  IST
 *       Revision:  1.1
 *       Compiler:  gcc
 *
 *         Author:  Jagdish Prajapati (JP), prajapatijagdish@gmail.com
 *        Company:  Emsoftronic
 *
 * =====================================================================================
 */

#include "framebuffer.h"

int main (void)
{
    int fd = fb_open("/dev/fb0");

    fb_printFullFbInfo(fd);

    fb_close(fd);
    return 0;
}
