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

char buffer[256];

int main(void)
{
    int len = 0;
    int fd = open("/dev/myshmem", O_RDONLY);
    if (fd < 0) {
        perror("device open");
        return -1;
    }

    while (1)
    {
        if ((len = read (fd, buffer, sizeof(buffer) - 1))  < 0) break;
        if (len > 0) {
            buffer[len] = '\0';
            printf("%s", buffer);
            fflush(stdout);
        }
        usleep(100000);
    }
    close(fd);
}

