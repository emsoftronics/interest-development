
#include <stdio.h>
#include "cutil.h"
#include <string.h>
#include "vmcutil.h"

static ccontext_t context = {0};

int my_strcmp(const char *s1, const char *s2) //66
{
    int *ret = NULL;
    ccontext_t *context = get_client_context("testserver");
    if (! context) return -9999;
    START_FCALL(context, 66)
    ADD_FCALL_ARG(context, s1, 1)
    ADD_FCALL_ARG(context, s2, 1)
    END_FCALL(context)
    UPDATE_PARG_MEM(context, s1, strlen(s1) + 1, 0)
    UPDATE_PARG_MEM(context, s2, strlen(s2) + 1, 1)
    ret = call_function(context);
    return (ret)?*ret:-9999;
}


int main(int argc, char **argv)
{
    if (argc < 3) return -1;

    do {
    printf("Comparision result: %d\n", my_strcmp(argv[1], argv[2]));
    } while (getchar() != (int)'x');
    return 0;
}

