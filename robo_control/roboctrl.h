/*
 * =====================================================================================
 *
 *       Filename:  roboctrl.h
 *
 *    Description:
 *
 *        Version:  1.0
 *        Created:  Wednesday 15 August 2018 10:42:28  IST
 *       Revision:  1.1
 *       Compiler:  gcc
 *
 *         Author:  Jagdish Prajapati (JP), prajapatijagdish@gmail.com
 *        Company:  Emsoftronic
 *
 * =====================================================================================
 */

#ifndef __ROBOCTRL_H__
#define __ROBOCTRL_H__

#define ROBO_LSENSOR     17
#define ROBO_RSENSOR     27

#define ROBO_RMOTOR_T0     0
#define ROBO_RMOTOR_T1     1

#define ROBO_LMOTOR_T0     2
#define ROBO_LMOTOR_T1     3

#define ROBO_SCAN_DELAY    1000

typedef enum {
    RD_FORWORD = 0,
    RD_LEFT,
    RD_RIGHT,
    RD_STOP,
    RD_BACKWORD,
} robodir_t;

extern int robo_init(void);
extern int robo_isInitDone(void);
extern void robo_setSpeed(int speed);
extern int robo_getSpeed(void);
extern void robo_incSpeed(void);
extern void robo_decSpeed(void);
extern void robo_setDirection(robodir_t dir);
extern robodir_t robo_getDirection(void);
extern int robo_startAutoControl(void);
extern int robo_isAutoControlOn(void);
extern void robo_stopAutoControl(void);
extern void robo_exit(void);


#endif /* __ROBOCTRL_H__ */
