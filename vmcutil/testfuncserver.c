
#include <stdio.h>
#include "cutil.h"
#include "vmcutil.h"
#include <string.h>

static void fcall_handler(int fid, int argc, void **args, void*ret, uint32_t *retsize)
{
    *(((int *)ret)) = strcmp(args[0], args[1]);
}

int main(int argc, char **argv)
{
    int sockfd;
    int fd;

   sockfd = make_local_server("testserver");
    while(1)
    {
        fd = wait_for_client(sockfd, -1);
        printf("Connected to client with fd : %d\n", fd);
        handle_ipc_calls(fd, fcall_handler);
    }
    close(sockfd);
    return -1;
}

