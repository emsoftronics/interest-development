/*
 * =====================================================================================
 *
 *       Filename:  testpwm.c
 *
 *    Description:
 *
 *        Version:  1.0
 *        Created:  Wednesday 15 August 2018 12:40:11  IST
 *       Revision:  1.1
 *       Compiler:  gcc
 *
 *         Author:  Jagdish Prajapati (JP), prajapatijagdish@gmail.com
 *        Company:  Emsoftronic
 *
 * =====================================================================================
 */

#include <stdio.h>
#include <stdlib.h>
#include "pwmctrl.h"
#define PERIOD 24000000L
#define DEF_DUTY 12000000L

int main(int argc, char *argv[])
{
    int duty_cycle = DEF_DUTY;
    int pin = 0;

    if (argc < 3 ) {
        printf("Insufficient Arguments!!\n");
        printf("Usage : %s <pin_no> <duty/x(stop)/s(start)/f(full duty)>\n", argv[0]);
        return -1;
    }

    pin = atoi(argv[1]);
    if ((pin >= 16) || (pin < 0)) {
        printf("Invalid pin assigned!! pin = %d\n", pin);
        return -1;
    }

    if (createPwmControl(atoi(argv[1])) < 0) {
        printf("Pwm device is not available\n");
        return -1;
    }

    if (setPeriod(pin, PERIOD) < 0) {
        printf("Unable to set period!!\n");
        return -1;
    }

    switch(argv[2][0])
    {
        case 's': setDutyCycle(pin, duty_cycle);
            break;
        case 'x': setDutyCycle(pin, 0);
            break;
        case 'f': setDutyCycle(pin, PERIOD);
            break;
        default : setDutyCycle(pin, atoi(argv[2]));
    }

    return 0;
}

