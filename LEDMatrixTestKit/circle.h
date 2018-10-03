/*
 * =====================================================================================
 *
 *       Filename:  circle.h
 *
 *    Description:  Draw of circle and arch support.
 *
 *        Version:  1.0
 *        Created:  Sunday 30 April 2017 12:33:52  IST
 *       Revision:  1.1
 *       Compiler:  gcc
 *
 *         Author:  Jagdish Prajapati (JP), prajapatijagdish@gmail.com
 *        Company:  Emsoftronic
 *
 * =====================================================================================
 */

#ifndef __CIRCLE_H__
#define __CIRCLE_H__

typedef void (*t_setpixel) (int, int, unsigned int);


extern void circle_Init(t_setpixel setpixel_hndlr);

//void circle_Draw(int x, int y, unsigned int outline_color, outline_width);

extern void circle_DrawFilled(int centre_x, int centre_y, int radius, unsigned int color);
extern void circle_DrawFrame(int centre_x, int centre_y, int radius, unsigned int color);

#endif /* End of __CIRCLE_H__ */

