/*
 * =====================================================================================
 *
 *       Filename:  circle.c
 *
 *    Description:  Definition of circle related functions
 *
 *        Version:  1.0
 *        Created:  Sunday 30 April 2017 12:50:51  IST
 *       Revision:  1.1
 *       Compiler:  gcc
 *
 *         Author:  Jagdish Prajapati (JP), prajapatijagdish@gmail.com
 *        Company:  Emsoftronic
 *
 * =====================================================================================
 */

#include "circle.h"
#define CIRCLE(cx,cy,r) ((x-(cx))*(x-(cx)) + (y-(cy))*(y-(cy)) - (r)*(r))

static t_setpixel SetPixel;

void circle_Init(t_setpixel setpixel_hndlr)
{
    SetPixel = setpixel_hndlr;
}

//void circle_Draw(int x, int y, unsigned int outline_color, outline_width);

void circle_DrawFilled(int centre_x, int centre_y, int radius, unsigned int color)
{
    int x, y;

    for (y = centre_y - radius - 1; y <= centre_y + radius; y++) {
        for (x = centre_x - radius - 1; x <= centre_x + radius; x++) {
            if (CIRCLE(centre_x, centre_y, radius) <= 0) {
                SetPixel(x,y,color);
            }
        }
    }
}

void circle_DrawFrame(int centre_x, int centre_y, int radius, unsigned int color)
{
    int x, y;

    for (y = centre_y - radius - 1; y <= centre_y + radius; y++) {
        for (x = centre_x - radius - 1; x <= centre_x + radius; x++) {
            if (CIRCLE(centre_x, centre_y, radius) == 0) {
                SetPixel(x,y,color);
            }
        }
    }
}
