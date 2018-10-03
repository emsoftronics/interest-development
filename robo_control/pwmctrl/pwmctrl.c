/*
 * =====================================================================================
 *
 *       Filename:  pwmctrl.c
 *
 *    Description:
 *
 *        Version:  1.0
 *        Created:  Wednesday 15 August 2018 11:34:59  IST
 *       Revision:  1.1
 *       Compiler:  gcc
 *
 *         Author:  Jagdish Prajapati (JP), prajapatijagdish@gmail.com
 *        Company:  Emsoftronic
 *
 * =====================================================================================
 */

#include "pwmctrl.h"
#include <stdio.h>
#include <unistd.h>

#define MAX_PATH_LEN        64

int createPwmControl(int pin)  /* pin (0...15)*/
{
    FILE *fp;
    char path[MAX_PATH_LEN];

    if (pin >= 16) return -1;

    snprintf(path, sizeof(path), SYS_PWMCHIP0);
    //check the pwm device exist.
    if (!(fp = fopen(path, "r"))) {
        printf("open %s failed\n", path);
        return -1;
    }
    fclose(fp);

    snprintf(path, sizeof(path), SYS_PWMCHIP0 "/pwm%d", pin);
    //check pwm control directory exists.
    if (!(fp = fopen(path, "r"))) {
      //  printf("open %s failed. May be need to create.\n", path);
        snprintf(path, sizeof(path), SYS_PWMCHIP0 "/export");
        //check pwm export file and open it.
        if (!(fp = fopen(path, "w"))) {
            printf("open %s failed\n", path);
            return -1;
        }

        fprintf(fp, "%d", pin);
        fclose(fp);
        usleep(10000);

        snprintf(path, sizeof(path), SYS_PWMCHIP0 "/pwm%d", pin);
        //check pwm control directory exists.
        if (!(fp = fopen(path, "r"))) {
            printf("open %s failed\n", path);
            return -1;
        }
        fclose(fp);
    }

    return 0;
}

int setPeriod(int pin, unsigned long period)
{
    FILE *fp;
    char path[MAX_PATH_LEN];

    if (pin >= 16) return -1;
    snprintf(path, sizeof(path), SYS_PWMCHIP0 "/pwm%d/period", pin);
    //check pwm export file and open it.
    if (!(fp = fopen(path, "w"))) {
        printf("open %s failed\n", path);
        return -1;
    }
    fprintf(fp, "%lu", period);
    fclose(fp);

    return 0;
}

long getPeriod(int pin)
{
    FILE *fp;
    char path[MAX_PATH_LEN];
    long period = -1;

    if (pin >= 16) return -1;
    snprintf(path, sizeof(path), SYS_PWMCHIP0 "/pwm%d/period", pin);
    //check pwm export file and open it.
    if (!(fp = fopen(path, "r"))) {
        printf("open %s failed\n", path);
        return -1;
    }
    fscanf(fp, "%ld", &period);
    fclose(fp);

    return period;
}

int setDutyCycle(int pin, unsigned long duty_cycle)
{
    FILE *fp;
    char path[MAX_PATH_LEN];

    if (pin >= 16) return -1;
    snprintf(path, sizeof(path), SYS_PWMCHIP0 "/pwm%d/duty_cycle", pin);
    //check pwm export file and open it.
    if (!(fp = fopen(path, "w"))) {
        printf("open %s failed\n", path);
        return -1;
    }
    fprintf(fp, "%lu", duty_cycle);
    fclose(fp);

    return 0;
}

long getDutyCycle(int pin)
{
    FILE *fp;
    char path[MAX_PATH_LEN];
    long duty_cycle = -1;

    if (pin >= 16) return -1;
    snprintf(path, sizeof(path), SYS_PWMCHIP0 "/pwm%d/duty_cycle", pin);
    //check pwm export file and open it.
    if (!(fp = fopen(path, "r"))) {
        printf("open %s failed\n", path);
        return -1;
    }
    fscanf(fp, "%ld", &duty_cycle);
    fclose(fp);

    return duty_cycle;
}

int setEnable(int pin, unsigned int enable)
{
    FILE *fp;
    char path[MAX_PATH_LEN];

    if (pin >= 16) return -1;
    snprintf(path, sizeof(path), SYS_PWMCHIP0 "/pwm%d/enable", pin);
    //check pwm export file and open it.
    if (!(fp = fopen(path, "w"))) {
        printf("open %s failed\n", path);
        return -1;
    }
    fprintf(fp, "%u", enable);
    fclose(fp);

    return 0;
}

int getEnable(int pin)
{
    FILE *fp;
    char path[MAX_PATH_LEN];
    int enable = -1;

    if (pin >= 16) return -1;
    snprintf(path, sizeof(path), SYS_PWMCHIP0 "/pwm%d/enable", pin);
    //check pwm export file and open it.
    if (!(fp = fopen(path, "r"))) {
        printf("open %s failed\n", path);
        return -1;
    }
    fscanf(fp, "%d", &enable);
    fclose(fp);

    return enable;
}




