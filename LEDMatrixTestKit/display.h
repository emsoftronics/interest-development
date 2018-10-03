/*
 * =====================================================================================
 *
 *       Filename:  display.h
 *
 *    Description:
 *
 *        Version:  1.0
 *        Created:  Sunday 30 April 2017 01:12:18  IST
 *       Revision:  1.1
 *       Compiler:  gcc
 *
 *         Author:  Jagdish Prajapati (JP), prajapatijagdish@gmail.com
 *        Company:  Emsoftronic
 *
 * =====================================================================================
 */

#ifndef __DISPLAY_H__
#define __DISPLAY_H__

#define DISP_DEV    "/dev/fb0"

extern void display_Init(void);
extern void display_Exit(void);
extern unsigned int display_GetWidth(void);
extern unsigned int display_GetHeight(void);
extern unsigned int display_GetPixel(int x, int y);
extern void display_SetPixel(int x, int y, unsigned int color);

#endif /* End of  __DISPLAY_H__ */
