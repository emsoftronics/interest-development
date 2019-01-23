
#include <stdio.h>
#include "cutil.h"
#include <string.h>
#include "vmcutil.h"

//static ccontext_t context = {0};

int my_strcmp(const char *s1, const char *s2) //66
{
    int *ret = NULL;
    ccontext_t *context = get_client_context("testserver", 2, strlen(s1) + strlen(s2) + 2);
    if (! context) return -9999;
    START_FCALL(context, 66)
    ADD_FCALL_ARG(context, s1, 1)
    ADD_FCALL_ARG(context, s2, 1)
    END_FCALL(context)
    UPDATE_PARG_MEM(context, s1, strlen(s1) + 1, 0)
    UPDATE_PARG_MEM(context, s2, strlen(s2) + 1, 1)
    ret = call_function(context);
    release_client_context(context);
    return (ret)?*ret:-9999;
}

long double my_sqrtl(long double x)
{
    long double *ret = NULL;
    ccontext_t *context = get_client_context("testserver", 1, sizeof(x));
    if (! context) return -9999;
    START_FCALL(context, 67)
    ADD_FCALL_ARG(context, x, 0)
    END_FCALL(context)
    ret = call_function(context);
    return (ret)?*ret:-1;
}

char *str1 = NULL;
char *str2 = NULL;

void *threadfunc(void *ctx)
{
    while(1) {
        printf("Comparision result: %d\n", my_strcmp(str1, str2));
        fflush(stdout);
        usleep(1000);
    }
}

int main(int argc, char **argv)
{
    long double x;
    pthread_t thread;
    if (argc < 3) return -1;
    str1 = argv[1];
    str2 = argv[2];

    //do {
    printf("Enter Sqrt input: ");
    scanf(" %Lf", &x);
//    pthread_create(&thread, NULL, threadfunc, NULL);
        while (1) {
            printf(" ____________\n");
            printf("V %8.4Lf\t= %8.4Lf\n", x, my_sqrtl(x));
            fflush(stdout);
            usleep(1000);
        }
   // } while (getchar() != (int)'x');
    return 0;
}

