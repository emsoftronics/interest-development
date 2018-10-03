/*
 * =====================================================================================
 *
 *       Filename:  main.c
 *
 *    Description:
 *
 *        Version:  1.0
 *        Created:  Sunday 30 April 2017 01:47:05  IST
 *       Revision:  1.1
 *       Compiler:  gcc
 *
 *         Author:  Jagdish Prajapati (JP), prajapatijagdish@gmail.com
 *        Company:  Emsoftronic
 *
 * =====================================================================================
 */

#include "led_disp.h"
#include "display.h"
#include "circle.h"

#define LED_OFF          0x007f0000
#define LED_ON          0x00ff0000



int main()
{
    int i, j, k = 0;
    //led_disp_Init();
    display_Init();
    //circle_Init((t_setpixel)led_disp_SetLedOn);
    circle_Init((t_setpixel)display_SetPixel);

    circle_DrawFrame( led_disp_GetWidth()/2, led_disp_GetHeight()/2, 20, LED_ON);
    sleep(10);
    led_disp_Exit();
    return 0;
}

