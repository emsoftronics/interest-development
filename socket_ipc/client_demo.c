/*
 * =====================================================================================
 *
 *       Filename:  client.c
 *
 *    Description:
 *
 *        Version:  1.0
 *        Created:  Monday 26 June 2017 12:47:41  IST
 *       Revision:  1.1
 *       Compiler:  gcc
 *
 *         Author:  Jagdish Prajapati (JP), prajapatijagdish@gmail.com
 *        Company:  Emsoftronic
 *
 * =====================================================================================
 */

#include <stdio.h>
#include "sipc.h"
#define PERSON_T_ID     225
#define EMPLOYEE_T_ID     20
typedef struct {
    char name [20];
    unsigned char age ;
    unsigned long int phone_no;
} person_t;


static person_t person, employee, *prsn;
static unsigned int p_id = 0;
void client_demo(void)
{
    int c = 0;
    int sd = sipc_connectToServer(DEFAULT_SOCKET_PATH);
    if (sd > 0) {
        if (sipc_allocDataBlock(sd, PERSON_T_ID, &person, sizeof(person)) < 0) {
            return;
        }

        do {
            c = getchar();
            switch(c){
            case 'r':
            case 'R':
                if (getchar() == 'e') {prsn = &employee; p_id = EMPLOYEE_T_ID;}
                else {prsn = &person; p_id = PERSON_T_ID;}
                if(sipc_getData(sd,p_id, prsn , sizeof(person_t)) < 0) {
                    printf("Data read through SIPC failed!!\n");
                }
                else {
                    printf("\n\tName : %s\n\tAge : %d\n\tPhone No. : %lu\n\n",
                            prsn->name, prsn->age, prsn->phone_no);
                    fflush(stdout);
                }
            break;
            case 'w':
            case 'W':
                if (getchar() == 'e') {prsn = &employee; p_id = EMPLOYEE_T_ID;}
                else {prsn = &person; p_id = PERSON_T_ID;}
                printf("\tName : ");
                scanf(" %[^\n]", prsn->name);
                printf("\tAge : ");
                scanf(" %d", &(prsn->age));
                printf("\tPhone No. : ");
                scanf(" %lu", &(prsn->phone_no));

                if(sipc_setData(sd,p_id,prsn, sizeof(person_t)) < 0) {
                    printf("Data write through SIPC failed!!\n");
                }
            break;
            }

        } while ((c != 'x') && (c != 'X'));
        close (sd);
    }
}
