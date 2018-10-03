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
#include "gpioctrl.h"

int main(int argc, char *argv[])
{
    int pin = 0;

    if (argc < 3 ) {
        printf("Insufficient Arguments!!\n");
        printf("Usage : %s <pin_no> <dir> [value]\n", argv[0]);
        return -1;
    }

    pin = atoi(argv[1]);

    if (createGpioControl(atoi(argv[1])) < 0) {
        printf("Gpio device is not available\n");
        return -1;
    }

    if (setDirection(pin, (argv[2][0] == 'i')? IODIR_IN : IODIR_OUT) < 0) {
        printf("Unable to set direction!!\n");
        return -1;
    }

    if ((argc >=4) && (argv[2][0] == 'o')) setValue(pin, atoi(argv[3]));

    printf("Current value of gpio%d = %d\n", pin, getValue(pin));

    return 0;
}

