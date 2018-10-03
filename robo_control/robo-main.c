/*
 * =====================================================================================
 *
 *       Filename:  robo-main.c
 *
 *    Description:
 *
 *        Version:  1.0
 *        Created:  Friday 17 August 2018 01:55:22  IST
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
#include <unistd.h>
#include "roboctrl.h"

int main(int argc, char *argv[])
{
    //char c;
    int speed = 12;

    if (robo_init() < 0) {
        printf("Robo initialization failed!!\n");
        return -1;
    }
    robo_startAutoControl();
    robo_setSpeed(12);

    if (argc > 1) speed = atoi(argv[1]);

    while(1) {
        /*
        printf("Choices:- \n\tf=>foreword, b=>break, l=>left, r=>right, s=>stop, x=>terminate\nEnter choice : ");
        fflush(stdout);
        scanf(" %c", &c);
        switch(c) {
            case 'f':
                robo_setDirection(RD_FORWORD);
                robo_incSpeed();
                break;
            case 'b':
                robo_setDirection(RD_FORWORD);
                robo_decSpeed();
                break;
            case 'l':
                robo_setDirection(RD_LEFT);
                break;
            case 'r':
                robo_setDirection(RD_RIGHT);
                break;
            case 's':
                robo_setDirection(RD_STOP);
                break;
        }
        if (c == 'x') break;
        */
        printf("Robo is running with speed : %d\n", speed);
        sleep(10000);
    }

    robo_stopAutoControl();
    robo_exit();
}
