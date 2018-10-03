/*
 * =====================================================================================
 *
 *       Filename:  gpioctrl.c
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

#include "gpioctrl.h"
#include <stdio.h>
#include <unistd.h>

#define MAX_PATH_LEN        64

int createGpioControl(int pin)
{
    FILE *fp;
    char path[MAX_PATH_LEN];

    snprintf(path, sizeof(path), SYS_GPIO);
    //check the gpio device exist.
    if (!(fp = fopen(path, "r"))) {
        printf("open %s failed\n", path);
        return -1;
    }
    fclose(fp);

    snprintf(path, sizeof(path), SYS_GPIO "/gpio%d", pin);
    //check gpio control directory exists.
    if (!(fp = fopen(path, "r"))) {
        //printf("open %s failed. May be need to create.\n", path);
        snprintf(path, sizeof(path), SYS_GPIO "/export");
        //check gpio export file and open it.
        if (!(fp = fopen(path, "w"))) {
            printf("open %s failed\n", path);
            return -1;
        }

        fprintf(fp, "%d", pin);
        fclose(fp);
        usleep(10000);

        snprintf(path, sizeof(path), SYS_GPIO "/gpio%d", pin);
        //check gpio control directory exists.
        if (!(fp = fopen(path, "r"))) {
            printf("open %s failed\n", path);
            return -1;
        }
        fclose(fp);
    }

    return 0;
}

int setDirection(int pin, const char *direction)
{
    FILE *fp;
    char path[MAX_PATH_LEN];

    snprintf(path, sizeof(path), SYS_GPIO "/gpio%d/direction", pin);
    //check gpio export file and open it.
    if (!(fp = fopen(path, "w"))) {
        printf("open %s failed\n", path);
        return -1;
    }
    fprintf(fp, "%s", direction);
    fclose(fp);

    return 0;
}

int getDirection(int pin)
{
    FILE *fp;
    char path[MAX_PATH_LEN];
    char dir[10];

    snprintf(path, sizeof(path), SYS_GPIO "/gpio%d/direction", pin);
    //check gpio export file and open it.
    if (!(fp = fopen(path, "r"))) {
        printf("open %s failed\n", path);
        return -1;
    }
    fscanf(fp, "%s", dir);
    fclose(fp);

    return (dir[0] == 'i') ? 1 : 0;
}

int setValue(int pin, int value)
{
    FILE *fp;
    char path[MAX_PATH_LEN];

    snprintf(path, sizeof(path), SYS_GPIO "/gpio%d/value", pin);
    //check gpio export file and open it.
    if (!(fp = fopen(path, "w"))) {
        printf("open %s failed\n", path);
        return -1;
    }
    fprintf(fp, "%d", (!!value));
    fclose(fp);

    return 0;
}

int getValue(int pin)
{
    FILE *fp;
    char path[MAX_PATH_LEN];
    int value = -1;

    snprintf(path, sizeof(path), SYS_GPIO "/gpio%d/value", pin);
    //check gpio export file and open it.
    if (!(fp = fopen(path, "r"))) {
        printf("open %s failed\n", path);
        return -1;
    }
    fscanf(fp, "%d", &value);
    fclose(fp);

    return value;
}

