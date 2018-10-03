/*
 * =====================================================================================
 *
 *       Filename:  roboctrl.c
 *
 *    Description:
 *
 *        Version:  1.0
 *        Created:  Wednesday 15 August 2018 10:40:50  IST
 *       Revision:  1.1
 *       Compiler:  gcc
 *
 *         Author:  Jagdish Prajapati (JP), prajapatijagdish@gmail.com
 *        Company:  Emsoftronic
 *
 * =====================================================================================
 */

#include "pwmctrl/pwmctrl.h"
#include "gpioctrl/gpioctrl.h"
#include "roboctrl.h"
#include <stdio.h>
#include <pthread.h>
#include <unistd.h>

#define PWM_PERIOD      24000000L
#define PWM_START       2000000L
#define PWM_STOP        0L


static unsigned long current_speed = PWM_PERIOD >> 1;
static unsigned long last_speed = PWM_PERIOD >> 1;

static robodir_t robo_last_turn = RD_LEFT;
static robodir_t last_robo_dir = RD_STOP;
static robodir_t current_robo_dir = RD_STOP;
static int robo_initialized = 0;
static int robo_autocontrol_started = 0;
static pthread_mutex_t robo_lock = PTHREAD_MUTEX_INITIALIZER;
static pthread_t robo_thread;

int robo_init(void)
{
    if (createPwmControl(ROBO_RMOTOR_T0) < 0) return -1;
    if (setPeriod(ROBO_RMOTOR_T0, PWM_PERIOD) < 0) return -1;
    if (setDutyCycle(ROBO_RMOTOR_T0, PWM_STOP) < 0) return -1;
    if (setEnable(ROBO_RMOTOR_T0, 1) < 0) return -1;

    if (createPwmControl(ROBO_RMOTOR_T1) < 0) return -1;
    if (setPeriod(ROBO_RMOTOR_T1, PWM_PERIOD) < 0) return -1;
    if (setDutyCycle(ROBO_RMOTOR_T1, PWM_STOP) < 0) return -1;
    if (setEnable(ROBO_RMOTOR_T1, 1) < 0) return -1;

    if (createPwmControl(ROBO_LMOTOR_T0) < 0) return -1;
    if (setPeriod(ROBO_LMOTOR_T0, PWM_PERIOD) < 0) return -1;
    if (setDutyCycle(ROBO_LMOTOR_T0, PWM_STOP) < 0) return -1;
    if (setEnable(ROBO_LMOTOR_T0, 1) < 0) return -1;

    if (createPwmControl(ROBO_LMOTOR_T1) < 0) return -1;
    if (setPeriod(ROBO_LMOTOR_T1, PWM_PERIOD) < 0) return -1;
    if (setDutyCycle(ROBO_LMOTOR_T1, PWM_STOP) < 0) return -1;
    if (setEnable(ROBO_LMOTOR_T1, 1) < 0) return -1;

    if (createGpioControl(ROBO_RSENSOR) < 0) return -1;
    if (setDirection(ROBO_RSENSOR, IODIR_IN) < 0) return -1;

    if (createGpioControl(ROBO_LSENSOR) < 0) return -1;
    if (setDirection(ROBO_LSENSOR, IODIR_IN) < 0) return -1;

    robo_initialized = 1;
    return 0;
}

int robo_isInitDone(void) {
    if (!robo_initialized) printf("Robo initialization is not done!!\n");
    return robo_initialized;
}

static void robo_updateMove(void)
{
    if ((last_robo_dir != current_robo_dir) || (last_speed != current_speed)) {
        switch(current_robo_dir)
        {
            case RD_FORWORD :
            case RD_BACKWORD :
                setDutyCycle(ROBO_RMOTOR_T0, current_speed);
                setDutyCycle(ROBO_RMOTOR_T1, PWM_STOP);
                setDutyCycle(ROBO_LMOTOR_T0, current_speed);
                setDutyCycle(ROBO_LMOTOR_T1, PWM_STOP);
                break;
            case RD_LEFT :
                setDutyCycle(ROBO_RMOTOR_T0, current_speed);
                setDutyCycle(ROBO_RMOTOR_T1, PWM_STOP);
                setDutyCycle(ROBO_LMOTOR_T0, PWM_STOP);
                setDutyCycle(ROBO_LMOTOR_T1, current_speed);
                robo_last_turn = RD_LEFT;
                break;
            case RD_RIGHT :
                setDutyCycle(ROBO_RMOTOR_T0, PWM_STOP);
                setDutyCycle(ROBO_RMOTOR_T1, current_speed);
                setDutyCycle(ROBO_LMOTOR_T0, current_speed);
                setDutyCycle(ROBO_LMOTOR_T1, PWM_STOP);
                robo_last_turn = RD_RIGHT;
                break;
            case RD_STOP :
                setDutyCycle(ROBO_RMOTOR_T0, PWM_STOP);
                setDutyCycle(ROBO_RMOTOR_T1, PWM_STOP);
                setDutyCycle(ROBO_LMOTOR_T0, PWM_STOP);
                setDutyCycle(ROBO_LMOTOR_T1, PWM_STOP);
                break;
        }
        last_speed = current_speed;
        last_robo_dir = current_robo_dir;
    }
}

void robo_setSpeed(int speed) /* 0 - 100 */
{
    if (!robo_isInitDone()) return;
    pthread_mutex_lock(&robo_lock);
    current_speed = (PWM_START * ( speed + 8)) / 9;
    if (current_speed > PWM_PERIOD) current_speed = PWM_PERIOD;
    if (current_speed < PWM_START) current_speed = PWM_STOP;
    robo_updateMove();
    pthread_mutex_unlock(&robo_lock);
}

int robo_getSpeed(void)
{
    int speed;

    if (!robo_isInitDone()) return 0;
    pthread_mutex_lock(&robo_lock);
    speed = current_speed;
    pthread_mutex_unlock(&robo_lock);
    speed = ((speed * 9)/PWM_START) - 8;
    if (speed > 100 ) return 100;
    if (speed < 0) return 0;
    return speed;
}

void robo_incSpeed(void) {
    if (!robo_isInitDone()) return;
    pthread_mutex_lock(&robo_lock);
    current_speed += (PWM_START * 11) / 100;
    if (current_speed > PWM_PERIOD) current_speed = PWM_PERIOD;
    if (current_speed < PWM_START) current_speed = PWM_START;
    robo_updateMove();
    pthread_mutex_unlock(&robo_lock);
}

void robo_decSpeed(void) {
    if (!robo_isInitDone()) return;
    pthread_mutex_lock(&robo_lock);
    current_speed -= (PWM_START * 11) / 100;
    if (current_speed > PWM_PERIOD) current_speed = PWM_PERIOD;
    if (current_speed < PWM_START) current_speed = PWM_STOP;
    robo_updateMove();
    pthread_mutex_unlock(&robo_lock);
}

void robo_setDirection(robodir_t dir)
{
    if (!robo_isInitDone()) return;
    pthread_mutex_lock(&robo_lock);
    current_robo_dir = dir;
    robo_updateMove();
    pthread_mutex_unlock(&robo_lock);
}

robodir_t robo_getDirection(void)
{
    robodir_t dir = 0;
    pthread_mutex_lock(&robo_lock);
    dir = current_robo_dir;
    pthread_mutex_unlock(&robo_lock);
    return dir;
}

static robodir_t robo_getLastTurn(void)
{
    robodir_t dir = 0;
    pthread_mutex_lock(&robo_lock);
    dir = robo_last_turn;
    pthread_mutex_unlock(&robo_lock);
    return dir;
}


static void *robo_handler(void *ctx)
{
    int loop = 0;
    int lsv, rsv;
    long turn_delay = 0;


    while(1) {
        pthread_mutex_lock(&robo_lock);
        loop = robo_autocontrol_started;
        pthread_mutex_unlock(&robo_lock);
        if (!loop) break;
        lsv = getValue(ROBO_LSENSOR);
        rsv = getValue(ROBO_RSENSOR);
        turn_delay = (robo_getSpeed() * ROBO_SCAN_DELAY)/100;
        if (!lsv && !rsv) {
            robo_setDirection(robo_getLastTurn());
            usleep(turn_delay);
        }
        else if (lsv && !rsv) {
            robo_setDirection(RD_LEFT);
            usleep(turn_delay);
        }
        else if (!lsv && rsv) {
            robo_setDirection(RD_RIGHT);
            usleep(turn_delay);
        }
        else {
            robo_setDirection(RD_FORWORD);
            usleep(ROBO_SCAN_DELAY);
        }
    }
    pthread_exit(NULL);
}

int robo_startAutoControl(void)
{
    int ret = -1;
    pthread_attr_t attr;

    if (!robo_isInitDone()) return -1;

    pthread_attr_init(&attr);
    pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_JOINABLE);
    robo_autocontrol_started = 1;
    if ((ret = pthread_create(&robo_thread, &attr, robo_handler, NULL)) != 0) {
        robo_autocontrol_started = 0;
    }
    pthread_attr_destroy(&attr);
    return ret;
}

int robo_isAutoControlOn(void)
{
    int ret;
    pthread_mutex_lock(&robo_lock);
    ret = robo_autocontrol_started;
    pthread_mutex_unlock(&robo_lock);
    return ret;
}

void robo_stopAutoControl(void)
{
    void *status;
    if (!robo_isInitDone()) return;

    if (robo_isAutoControlOn()) {
        pthread_mutex_lock(&robo_lock);
        robo_autocontrol_started = 0;
        pthread_mutex_unlock(&robo_lock);
        pthread_join(robo_thread, &status);
    }
}

void robo_exit(void)
{
    if (!robo_isInitDone()) return;

    if (robo_isAutoControlOn()) {
        robo_stopAutoControl();
    }

    current_speed = PWM_PERIOD >> 1;
    last_speed = PWM_PERIOD >> 1;

    robo_last_turn = RD_LEFT;
    last_robo_dir = RD_STOP;
    current_robo_dir = RD_STOP;
    robo_updateMove();
    robo_initialized = 0;
    setEnable(ROBO_LMOTOR_T1, 0);
}

