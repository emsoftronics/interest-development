
#include <stdio.h>
#include "cutil.h"
#include "vmcutil.h"
#include <string.h>
#include <math.h>

static char *reverse(char *x, int begin, int end)
{
   char c;

   if (begin >= end)
      return;
   c          = *(x+begin);
   *(x+begin) = *(x+end);
   *(x+end)   = c;

   reverse(x, ++begin, --end);
   return x;
}

static void fcall_handler(int fid, int argc, void **args, void*ret, uint32_t *retsize)
{
    switch (fid) {
    case 66:
        *(((int *)ret)) = strcmp(args[0], args[1]);
        break;
    case 67:
        *(((long double *)ret)) = sqrtl(*((long double *)args[0]));
        break;
    case 68:
        reverse((char *)args[0], *((int*)args[1]), *((int*)args[2]));
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


