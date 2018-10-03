/*
 * =====================================================================================
 *
 *       Filename:  gpioctrl.h
 *
 *    Description:
 *
 *        Version:  1.0
 *        Created:  Wednesday 15 August 2018 11:42:38  IST
 *       Revision:  1.1
 *       Compiler:  gcc
 *
 *         Author:  Jagdish Prajapati (JP), prajapatijagdish@gmail.com
 *        Company:  Emsoftronic
 *
 * =====================================================================================
 */

#ifndef __GPIOCTRL_H__
#define __GPIOCTRL_H__

#define SYS_GPIO     "/sys/class/gpio"

#define IODIR_IN    "in"
#define IODIR_OUT   "out"

extern int createGpioControl(int pin);
extern int setDirection(int pin, const char *direction);
extern int getDirection(int pin);
extern int setValue(int pin, int value);
extern int getValue(int pin);

#endif /*  __PWMCTRL_H__ */
