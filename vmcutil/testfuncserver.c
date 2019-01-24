
#include <stdio.h>
#include "cutil.h"
#include "vmcutil.h"
#include <string.h>
#include <math.h>

static char *reverse(char *x, int begin, int end)
{
   char c;
   int i, length = (end - begin)/2;
   if (begin >= end)
      return;
   for ( i = begin; i < begin + length; i++) {
        c          = *(x+i);
        *(x+i) = *(x + end - i);
        *(x+end - i)   = c;
    }
   return x;
}

static void fcall_handler(int fid, int argc, void **args, void*ret, uint32_t *retsize)
{
    long double t1, t2;
    switch (fid) {
    case 66:
        *(((int *)ret)) = strcmp(args[0], args[1]);
        break;
    case 67:
        *(((long double *)ret)) = sqrtl(*((long double *)args[0]));
        break;
    case 68:
        t1 = get_millisecond_time();
        reverse((char *)args[0], *((int*)args[1]), *((int*)args[2]));
        t2 = get_millisecond_time();
        printf("%Lf ms\n", t2-t1);
        break;
    }

}

int main(int argc, char **argv)
{
#ifdef DEFAULT_FCALL_SERVER
    RUN_DEFAULT_FCALL_SERVER(fcall_handler);
#else
    int sockfd;
    int fd;

    sockfd = make_local_server("hello");
    while(1)
    {
        fd = wait_for_client(sockfd, -1);
        printf("Connected to client with fd : %d\n", fd);
        handle_ipc_calls(fd, fcall_handler);
    }
    close(sockfd);
#endif
    return -1;
}


