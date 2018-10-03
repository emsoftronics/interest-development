/*
 * =====================================================================================
 *
 *       Filename:  led_matrix.c
 *
 *    Description:
 *
 *        Version:  1.0
 *        Created:  Sunday 14 May 2017 07:09:27  IST
 *       Revision:  1.1
 *       Compiler:  gcc
 *
 *         Author:  Jagdish Prajapati (JP), prajapatijagdish@gmail.com
 *        Company:  Emsoftronic
 *
 * =====================================================================================
 */

#include "display.h"
#include "led_disp.h"


static unsigned int led_disp_width = 0;
static unsigned int led_disp_height = 0;
static int led_pitch = LED_PITCH;

static void MakeLED(int centre_x, int centre_y, int radius, unsigned int color)
{
    int x, y;
#define CIRCLE(cx,cy,r) ((x-(cx))*(x-(cx)) + (y-(cy))*(y-(cy)) - (r)*(r))
    for (y = centre_y - radius - 1; y <= centre_y + radius; y++) {
        for (x = centre_x - radius - 1; x <= centre_x + radius; x++) {
            if (CIRCLE(centre_x, centre_y, radius) <= 0) {
                display_SetPixel(x,y,color);
            }
        }
    }
}

static void DrawLedMatrix(unsigned int width, unsigned int height)
{
    int i, j;

    led_disp_width = 0;
    led_disp_height = 0;
    if (led_pitch < LED_SIZE)
        led_pitch = LED_SIZE;

    for (j = led_pitch; j < height - led_pitch ; j+=led_pitch, led_disp_height++)
        for (i = led_pitch; i < width - led_pitch; i+=led_pitch) {
            MakeLED( i, j, LED_SIZE/2, LED_DISP_COLOR);
            if (j == led_pitch)
                led_disp_width++;
        }
}


void led_disp_Init(void)
{
    display_Init();
    DrawLedMatrix( display_GetWidth(), display_GetHeight());
}

void led_disp_Exit(void)
{
    display_Exit();
}


unsigned int led_disp_GetWidth(void)
{
    return led_disp_width;
}

unsigned int led_disp_GetHeight(void)
{
    return led_disp_height;
}

void led_disp_SetLedOn(int x, int y, int color)
{
    if ((x < led_disp_width) && (y < led_disp_height)) {
        MakeLED(x*led_pitch, y*led_pitch, LED_SIZE/2, color);
    }
}

