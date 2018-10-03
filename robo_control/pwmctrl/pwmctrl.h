/*
 * =====================================================================================
 *
 *       Filename:  pwmctrl.h
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

#ifndef __PWMCTRL_H__
#define __PWMCTRL_H__

#define SYS_PWMCHIP0     "/sys/class/pwm/pwmchip0"

extern int createPwmControl(int pin);  /* pin (0...15)*/
extern int setPeriod(int pin, unsigned long period);
extern long getPeriod(int pin);
extern int setDutyCycle(int pin, unsigned long duty_cycle);
extern long getDutyCycle(int pin);
extern int setEnable(int pin, unsigned int enable);
extern int getEnable(int pin);

#endif /*  __PWMCTRL_H__ */
