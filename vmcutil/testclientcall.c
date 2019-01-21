
#include <stdio.h>
#include "cutil.h"
#include <string.h>
#include "vmcutil.h"

static ccontext_t context = {0};

int my_strcmp(const char *s1, const char *s2) //66
{
    if ((context.sockfd <= 2)||(context.smemfd <= 2)) {
        if (init_client_context(&context, "testserver", 500)) {
            printf("client context initialization error!!\n");
            return -2;
        }
    }
    START_FCALL((&context), 66)
    ADD_FCALL_ARG((&context), s1, 1)
    ADD_FCALL_ARG((&context), s2, 1)
    END_FCALL((&context))
    UPDATE_PARG_MEM((&context), s1, strlen(s1) + 1, 0)
    UPDATE_PARG_MEM((&context), s2, strlen(s2) + 1, 1)

    if (send_call(&context) == 0) {
        return *((int *)get_ret_ptr(&context));
    }

    return -2;
}


int main(int argc, char **argv)
{
    if (argc < 3) return -1;

    do {
    printf("Comparision result: %d\n", my_strcmp(argv[1], argv[2]));
    } while (getchar() != (int)'x');
    return 0;
}
