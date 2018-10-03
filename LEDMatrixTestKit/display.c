/*
 * =====================================================================================
 *
 *       Filename:  display.c
 *
 *    Description:
 *
 *        Version:  1.0
 *        Created:  Sunday 30 April 2017 01:17:44  IST
 *       Revision:  1.1
 *       Compiler:  gcc
 *
 *         Author:  Jagdish Prajapati (JP), prajapatijagdish@gmail.com
 *        Company:  Emsoftronic
 *
 * =====================================================================================
 */

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <linux/fb.h>
#include <sys/mman.h>
#include <sys/kd.h>

#include "display.h"

#define XMARGIN 5
#define YMARGIN 5

static int fbfd = 0;
static struct fb_var_screeninfo vinfo;
static struct fb_fix_screeninfo finfo;
static char *fbp = NULL;
static long int screensize = 0;
static int tty_fd = 0;
void display_Init(void)
{

    /* Open the file for reading and writing */
    fbfd = open(DISP_DEV, O_RDWR);
    if (!fbfd) {
        printf("Error: cannot open framebuffer device.\n");
        exit(1);
    }
    printf("The framebuffer device was opened successfully.\n");

    /* Get fixed screen information */
    if (ioctl(fbfd, FBIOGET_FSCREENINFO, &finfo)) {
        printf("Error reading fixed information.\n");
        exit(2);
    }

    /* Get variable screen information */
    if (ioctl(fbfd, FBIOGET_VSCREENINFO, &vinfo)) {
        printf("Error reading variable information.\n");
        exit(3);
    }

    vinfo.grayscale=0;
    vinfo.bits_per_pixel=32;
    vinfo.xres_virtual = 1366;
    vinfo.yres_virtual= 768;
    vinfo.xres = 1366;
    vinfo.yres= 768;
    if (ioctl(fbfd, FBIOPUT_VSCREENINFO, &vinfo)) {
        printf("Error writing variable information.\n");
        exit(4);
    }

    /* Figure out the size of the screen in bytes */
    screensize = vinfo.xres * vinfo.yres * vinfo.bits_per_pixel / 8;

    /* Map the device to memory */
    fbp = (char *)mmap(0, screensize, PROT_READ | PROT_WRITE, MAP_SHARED,
        fbfd, 0);
    if ((int)fbp == -1) { printf("Error: failed to map "
        "framebuffer device to memory.\n"); exit(5);
    }
    printf("The framebuffer device was mapped to memory successfully.\n");

    tty_fd = open("/dev/tty0", O_RDWR);
    if (ioctl(tty_fd,KDSETMODE,KD_GRAPHICS)) {
        printf("Error Setting graphics mode.\n");
        exit(6);
    }
    printf("The graphic mode has been set.\n");
}

void display_Exit(void)
{
    if (ioctl(tty_fd,KDSETMODE,KD_TEXT)) {
        printf("Error Setting text mode.\n");
        exit(7);
    }
    printf("The text mode has been set.\n");
    close(tty_fd);
    munmap(fbp, screensize);
    close(fbfd);
}


unsigned int display_GetWidth(void)
{
    return vinfo.xres - XMARGIN;
}

unsigned int display_GetHeight(void)
{
    return vinfo.yres - YMARGIN;
}

unsigned int display_GetPixel(int x, int y)
{
    return 0;
}

void display_SetPixel(int x, int y, unsigned int color)
{
    long int location = 0;
    if ((x < vinfo.xres - XMARGIN) && (y < vinfo.yres - YMARGIN) && (x >= 0) && (y >= 0)) {
        location = (x+vinfo.xoffset) * (vinfo.bits_per_pixel/8) +
                (y+vinfo.yoffset) * finfo.line_length;
        if (vinfo.bits_per_pixel == 32) {
            *(fbp + location) = (char)(color & 0xff);        // blue
            *(fbp + location + 1) = (char)((color>>8) & 0xff); // green
            *(fbp + location + 2) = (char)((color>>16) & 0xff);// red
            *(fbp + location + 3) = (char)((color>>24) & 0xff);// transparency
            //location += 4;
        } else  { //assume 16bpp
            int b = color & 0xff;        // blue
            int g = (color>>8) & 0xff;   // green
            int r = (color>>16) & 0xff;  // red
            unsigned short int t = r<<11 | g << 5 | b;
            *((unsigned short int*)(fbp + location)) = t;
        }
    }
}
