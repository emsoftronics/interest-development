/*
 * =====================================================================================
 *
 *       Filename:  shared_comm.c
 *
 *    Description:
 *
 *        Version:  1.0
 *        Created:  Monday 17 September 2018 06:36:17  IST
 *       Revision:  1.1
 *       Compiler:  gcc
 *
 *         Author:  Jagdish Prajapati (JP), prajapatijagdish@gmail.com
 *        Company:  Emsoftronic
 *
 * =====================================================================================
 */
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <error.h>
#include <string.h>

char buffer[256];

int main(void)
{
    int len = 0, wlen = 0, sindex = 0;
    int fd = open("/dev/myshmem", O_WRONLY);
    if (fd < 0) {
        perror("device open");
        return -1;
    }

    while (1)
    {
        printf("Enter the data to transfer: ");
        fflush(stdout);
        scanf(" %[^\n]", buffer);
        len = strlen(buffer);
        sindex = 0;
        printf("Please wait for data transmission completion....\n");
        fflush(stdout);
        while((wlen = write(fd, &buffer[sindex], len)) >= 0) {
            if (wlen == len) break;
            printf("sindex = %d, total length = %d, written length = %d\n", sindex, len, wlen);
            sindex += wlen;
            len -= wlen;
            usleep(1000);
        }
    }
    close(fd);
}

