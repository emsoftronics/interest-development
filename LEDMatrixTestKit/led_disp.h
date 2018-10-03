/*
 * =====================================================================================
 *
 *       Filename:  led_disp.h
 *
 *    Description:
 *
 *        Version:  1.0
 *        Created:  Sunday 14 May 2017 08:03:31  IST
 *       Revision:  1.1
 *       Compiler:  gcc
 *
 *         Author:  Jagdish Prajapati (JP), prajapatijagdish@gmail.com
 *        Company:  Emsoftronic
 *
 * =====================================================================================
 */

#ifndef __LED_DISP_H__
#define __LED_DISP_H__

#define LED_DISP_COLOR      0x003f0000
#define LED_SIZE            10      //in original display pixels
#define LED_PITCH           10      //in original display pixels

extern void led_disp_Init(void);
extern void led_disp_Exit(void);
extern unsigned int led_disp_GetWidth(void);
extern unsigned int led_disp_GetHeight(void);
extern void led_disp_SetLedOn(int x, int y, int color);
#endif /* End of  __LED_DISP_H__ */
