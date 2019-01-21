
#include <stdio.h>
#include "cutil.h"
#include "vmcutil.h"
#include <string.h>

char buffer[128];

static ccontext_t context = {0};

int main(int argc, char **argv)
{
    int sockfd;
    int fd;
    int len;

   sockfd = make_local_server(argv[1]);
    while(1)
    {
        fd = wait_for_client(sockfd, -1);
        printf("Connected to client with fd : %d\n", fd);

        while(watch_fd(fd, -1) >= 0) {
            /*
            //scanf(" %[^\n]", buffer);
            memset(buffer, 0, sizeof(buffer));
            len = wait_for_response(fd, 100, buffer, sizeof(buffer));
            clear_rx_buffer(sockfd);
            if (len < 0) break;
            else if (len > 0) {
                buffer[len] = '\0';
                printf("%s\n",buffer);
                send_data(fd, buffer, strlen(buffer));
            }
            */
            context.sockfd = fd;
            if (rcv_call(&context) == 0) {
                fcall_hdr_t *chdr = context.smemref;
                printf("%s: %d\n", __func__, __LINE__);
                int *ret = get_ret_ptr(&context);
                printf("%s: %d\n", __func__, __LINE__);
                if (chdr->methodid == 66) {
                printf("%s: %d\n", __func__, __LINE__);
                    printf ("%s <> %s\n", get_arg_ptr(&context, 0), get_arg_ptr(&context, 1));
                    *ret = strcmp(get_arg_ptr(&context, 0), get_arg_ptr(&context, 1));
                    printf("strcmp : %d\n", ret);
                }
                else {
                printf("%s: %d\n", __func__, __LINE__);
                    *ret = -2;
                }
                printf("%s: %d\n", __func__, __LINE__);
                context.frame.size = sizeof(int);
                context.frame.offset = chdr->endoff;
                clear_rx_buffer(context.sockfd);
                if (send_data(context.sockfd, &context.frame, sizeof(qframe_t)) < sizeof(qframe_t)) {
                    reset_context(&context);
                    break;
                }
                printf("%s: %d\n", __func__, __LINE__);
            }
            else break;
        }
        reset_context(&context);

        //if (getchar() == (int)'x') break;
    }
    close(sockfd);
    return -1;
}
