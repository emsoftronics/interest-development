/*
 * =====================================================================================
 *
 *       Filename:  framebuffer.c
 *
 *    Description:
 *
 *        Version:  1.0
 *        Created:  Thursday 25 May 2017 11:19:50  IST
 *       Revision:  1.1
 *       Compiler:  gcc
 *
 *         Author:  Jagdish Prajapati (JP), prajapatijagdish@gmail.com
 *        Company:  Emsoftronic
 *
 * =====================================================================================
 */


#include <stdio.h>
#include <fcntl.h>
#include <stdlib.h>
#include <stdint.h>
#include <unistd.h>
#include <string.h>
#include <signal.h>
#include <errno.h>
#include <sys/ioctl.h>
#include <sys/mman.h>
#include <sys/types.h>
#include <sys/stat.h>
#include "framebuffer.h"

#define FB_ERR(ret) do{ if((int)(ret) < 0){ perror(__func__); \
                    return (int)(ret);}}while(0)
#define FB_ERRV do{ perror(__func__); return;}while(0)

#define MKINT(data, offset, len)  (((data)&(~(~((unsigned int)0) << (len)))) << (offset))

int fb_Init(t_framebuffer *fb)
{
    int ret = -ENOMEM;

    if (fb == NULL) {
        errno = ENOMEM;
        FB_ERR(ret);
    }

    fb->fb_fd = open(fb->fb_dev_node, O_RDWR, 0);
    FB_ERR(fb->fb_fd);

    ret = ioctl(fb->fb_fd, FBIOGET_FSCREENINFO, &(fb->fb_fix));
    FB_ERR(ret);

    ret = ioctl(fb->fb_fd, FBIOGET_VSCREENINFO, &(fb->fb_var));
    FB_ERR(ret);

    fb->fb_addr = (char *)mmap(0, fb->fb_fix.smem_len,
                PROT_READ | PROT_WRITE, MAP_SHARED, fb->fb_fd, 0);
    FB_ERR(fb->fb_addr);

    return 0;
}


void fb_Exit(t_framebuffer *fb)
{
    if (fb == NULL) FB_ERRV;
    if ((fb->fb_addr != NULL)
            && (munmap(fb->fb_addr, fb->fb_fix.smem_len) < 0)) FB_ERRV;
    if (close(fb->fb_fd) < 0) FB_ERRV;
}


int fb_PrintCustomFbInfo(t_framebuffer *fb)
{
    if ((fb == NULL) || (fb->fb_fd <= 0)) {
        printf("%s : Frame buffer not initialized or NULL input.\n", __func__);
        return -ENOMEM;
    }
    printf("\n\t\tCustomizable Framebuffer information \n");
    printf("--------------------------------------------------------------\n");
    printf("\tfb->xres = %4d\n",  fb->fb_var.xres);
    printf("\tfb->yres = %4d\n",  fb->fb_var.yres);
    printf("\tfb->xres_virtual = %4d\n",  fb->fb_var.xres_virtual);
    printf("\tfb->yres_virtual = %4d\n",  fb->fb_var.yres_virtual);
    printf("\tfb->xoffset = %4d\n",  fb->fb_var.xoffset);
    printf("\tfb->yoffset = %4d\n",  fb->fb_var.yoffset);
    printf("\tfb->bits_per_pixel = %2d\n",  fb->fb_var.bits_per_pixel);
    printf("\tfb->grayscale = %d\n",  fb->fb_var.grayscale);
    printf("\tPixel format : RGBX_%d%d%d%d\n",fb->fb_var.red.length,
                                                 fb->fb_var.green.length,
                                                 fb->fb_var.blue.length,
                                                 fb->fb_var.transp.length);
    printf("\n=>Begin of bitfields(Byte ordering offsets):-\n");
    printf("\tfb->red.offset    : %2d\n", fb->fb_var.red.offset);
    printf("\tfb->green.offset  : %2d\n", fb->fb_var.green.offset);
    printf("\tfb->blue.offset   : %2d\n", fb->fb_var.blue.offset);
    printf("\tfb->transp.offset : %2d\n\n", fb->fb_var.transp.offset);
    printf("\tfb->nonstd (pixel format) : %d\n\n",fb->fb_var.nonstd);
    printf("\tfb->activate : %d\n\n", fb->fb_var.activate);
    printf("\tfb->height (in mm) = %4d\n",  fb->fb_var.height);
    printf("\tfb->width (in mm) =  %4d\n",  fb->fb_var.width);
    printf("\tfb->accel_flags(no more useful) : %d\n\n", fb->fb_var.accel_flags);
    printf("\n=>Timing: All values in pixclocks, except pixclock (of course)\n");
    printf("\tfb->pixclock = %d\n",  fb->fb_var.pixclock);
    printf("\tfb->left_margin = %d\n",  fb->fb_var.left_margin);
    printf("\tfb->right_margin = %d\n",  fb->fb_var.right_margin);
    printf("\tfb->upper_margin = %d\n",  fb->fb_var.upper_margin);
    printf("\tfb->lower_margin = %d\n",  fb->fb_var.lower_margin);
    printf("\tfb->hsync_len = %d\n",  fb->fb_var.hsync_len);
    printf("\tfb->vsync_len = %d\n",  fb->fb_var.vsync_len);
    printf("\tfb->sync = %d\n",  fb->fb_var.sync);
    printf("\tfb->vmode = %d\n",  fb->fb_var.vmode);
    printf("\tfb->rotate = %d\n",  fb->fb_var.rotate);
    printf("\tfb->colorspace = %d\n",  fb->fb_var.colorspace);
    printf("--------------------------------------------------------------\n");

    return 0;
}

int fb_PrintFixedFbInfo(t_framebuffer *fb)
{
    if ((fb == NULL) || (fb->fb_fd <= 0)) {
        printf("%s : Frame buffer not initialized or NULL input.\n", __func__);
        return -ENOMEM;
    }
    printf("\n\t\tFixed Framebuffer information \n");
    printf("--------------------------------------------------------------\n");
    printf("\tfb->id = \"%s\"\n",  fb->fb_fix.id);
    printf("\tfb->smem_start = 0x%x\n",  fb->fb_fix.smem_start);
    printf("\tfb->smem_len = %lu\n",  fb->fb_fix.smem_len);
    printf("\tfb->type = %d\n",  fb->fb_fix.type);
    printf("\tfb->type_aux = %d\n",  fb->fb_fix.type_aux);
    printf("\tfb->visual = %d\n",  fb->fb_fix.visual);
    printf("\tfb->xpanstep = %d\n",  fb->fb_fix.xpanstep);
    printf("\tfb->ypanstep = %d\n",  fb->fb_fix.ypanstep);
    printf("\tfb->ywrapstep = %d\n",  fb->fb_fix.ywrapstep);
    printf("\tfb->line_length = %d\n",  fb->fb_fix.line_length);
    printf("\tfb->mmio_start = 0x%x\n",  fb->fb_fix.mmio_start);
    printf("\tfb->mmio_len = %lu\n",  fb->fb_fix.mmio_len);
    printf("\tfb->accel = %d\n",  fb->fb_fix.accel);
    printf("\tfb->capabilities = %d\n",  fb->fb_fix.capabilities);
    printf("--------------------------------------------------------------\n");

    return 0;
}

int fb_PrintFullFbInfo(t_framebuffer *fb)
{
    if (fb_printFixedFbInfo(fb->fb_fd) < 0)
        return -ENOMEM;

    return fb_printCustomFbInfo(fb->fb_fd);
}


void fb_PutPixel(t_framebuffer *fb, int pix_x, int pix_y, unsigned int pix_color)
{
    int location = 0;
    unsigned int *pixel = NULL;
    if ((fb == NULL) || (fb->fb_addr == NULL)) {
        printf("%s : Null pointer as input detected.", __func__);
        return;
    }

    if ((pix_x >= fb->fb_var.xres) || (pix_x < 0) || (pix_y >= fb->fb_var.yres)
            || (pix_y < 0) || (pix_y + fb->fb_var.yoffset
                >= fb->fb_var.yres_virtual) || ((pix_x + fb->fb_var.xoffset)
                    *(fb->fb_var.bits_per_pixel >> 3) >= fb->fb_fix.line_length))
        return;

    location = (pix_x + fb->fb_var.xoffset)*(fb->fb_var.bits_per_pixel >> 3)
        + (pix_y + fb->fb_var.yoffset)*fb->fb_fix.line_length;

    pixel = (unsigned int *)(fb->fb_addr + location);

    *pixel = (*pixel) & ((~((unsigned int)0)) << fb->fb_var.bits_per_pixel)
        || MKINT(pix_color, fb->fb_var.blue.offset, fb->fb_var.blue.length)
        || MKINT((pix_color >> 8), fb->fb_var.green.offset, fb->fb_var.green.length)
        || MKINT((pix_color >> 16), fb->fb_var.red.offset, fb->fb_var.red.length)
        || MKINT((pix_color >>24), fb->fb_var.transp.offset, fb->fb_var.transp.length);
}

unsigned int fb_GetPixel(t_framebuffer *fb, int pix_x, int pix_y)
{
    int location = 0;
    unsigned int *pixel = NULL;
    unsigned int color;
    if ((fb == NULL) || (fb->fb_addr == NULL)) {
        printf("%s : Null pointer as input detected.", __func__);
        return 0;
    }

    if ((pix_x >= fb->fb_var.xres) || (pix_x < 0) || (pix_y >= fb->fb_var.yres)
            || (pix_y < 0) || (pix_y + fb->fb_var.yoffset
                >= fb->fb_var.yres_virtual) || ((pix_x + fb->fb_var.xoffset)
                    *(fb->fb_var.bits_per_pixel >> 3) >= fb->fb_fix.line_length))
        return 0;

    location = (pix_x + fb->fb_var.xoffset)*(fb->fb_var.bits_per_pixel >> 3)
        + (pix_y + fb->fb_var.yoffset)*fb->fb_fix.line_length;

    pixel = (unsigned int *)(fb->fb_addr + location);

    color = MKINT((*pixel) >> fb->fb_var.blue.offset, 0, fb->fb_var.blue.length)
        || MKINT((*pixel) >> fb->fb_var.green.offset, 8, fb->fb_var.green.length)
        || MKINT((*pixel) >> fb->fb_var.red.offset, 16, fb->fb_var.red.length)
        || MKINT((*pixel) >> fb->fb_var.transp.offset, 24, fb->fb_var.transp.length);

    return color;
}



int fb_SetVisibleScreenPos(t_framebuffer *fb, int left, int top)
{
    int xoffset = 0, yoffset = 0;

    if ((fb == NULL) || (fb->fb_addr == NULL)) {
        printf("%s : Null pointer as input detected.", __func__);
        return -ENOMEM;
    }

    if ((left >= 0) && (left + fb->fb_var.xres < fb->fb_var.xres_virtual))
        xoffset = left;
    else
        xoffset = fb->fb_var.xoffset;

    if ((top >=0) && (top + fb->fb_var.yres < fb->fb_var.yres_virtual))
        yoffset = top;
    else
        yoffset = fb->fb_var.yoffset;

    if ( (xoffset != fb->fb_var.xoffset) || (yoffset != fb->fb_var.yoffset)) {

    }
}

int fb_SetScreenSize(t_framebuffer *fb, unsigned int width, int height )
{
    if ((fb == NULL) || (fb->fb_addr == NULL)) {
        printf("%s : Null pointer as input detected.", __func__);
        return -ENOMEM;
}

