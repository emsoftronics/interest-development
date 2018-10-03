/*
 * =====================================================================================
 *
 *       Filename:  framebuffer.h
 *
 *    Description:
 *
 *        Version:  1.0
 *        Created:  Thursday 25 May 2017 11:14:44  IST
 *       Revision:  1.1
 *       Compiler:  gcc
 *
 *         Author:  Jagdish Prajapati (JP), prajapatijagdish@gmail.com
 *        Company:  Emsoftronic
 *
 * =====================================================================================
 */

#ifndef __FRAMEBUFFER_h__
#define __FRAMEBUFFER_h__

#include <linux/fb.h>

typedef struct {
    char fb_dev_node[24];
    int fb_fd;
    char *fb_addr;
    struct fb_fix_screeninfo fb_fix;
    struct fb_var_screeninfo fb_var;
} t_framebuffer;

typedef struct {
    unsigned char blue;
    unsigned char green;
    unsigned char red;
    unsigned char transp;
} t_color;

extern int fb_Init(t_framebuffer *fb);
extern void fb_Exit(t_framebuffer *fb);
extern int fb_PrintCustomFbInfo(t_framebuffer *fb);
extern int fb_PrintFixedFbInfo(t_framebuffer *fb);
extern int fb_PrintFullFbInfo(t_framebuffer *fb);

#endif /*  __FRAMEBUFFER_h__ */
