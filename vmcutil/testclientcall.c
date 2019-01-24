
#include <stdio.h>
#include "cutil.h"
#include <string.h>
#include "vmcutil.h"

//static ccontext_t context = {0};

int my_strcmp(const char *s1, const char *s2) //66
{
    int ret = -0xfffffff;
#ifdef DEFAULT_CLIENT_CONTEXT
    DCC_START_CALL(66, 2, strlen(s1) + strlen(s2) + 2);
    DCC_ADD_ARG(s1, 1);
    DCC_ADD_ARG(s2, 1);
    DCC_ARG_OVER();
    DCC_ADD_APTR_MEM(s1, strlen(s1) + 1, 0);
    DCC_ADD_APTR_MEM(s2, strlen(s2) + 1, 1);
    DCC_RET_VAL(ret);
    DCC_END_CALL();
#endif
    return ret;
}

long double my_sqrtl(long double x) //67
{
    long double ret = -1.0e28;
#ifdef DEFAULT_CLIENT_CONTEXT
    DCC_START_CALL(67, 1, sizeof(x));
    DCC_ADD_ARG(x, 0);
    DCC_ARG_OVER();
    DCC_RET_VAL(ret);
    DCC_END_CALL();
#endif
    return ret;
}

char *str1 = NULL;
char *str2 = NULL;

void *threadfunc(void *ctx)
{
    while(1) {
        printf("Comparision result: %d\n", my_strcmp(str1, str2));
        fflush(stdout);
        usleep(100);
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
#if 1
    pthread_create(&thread, NULL, threadfunc, NULL);
#endif
        while (1) {
#if 0
            printf("Comparision result: %d\n", my_strcmp(str1, str2));
#else
            printf(" ____________\n");
            printf("V %8.4Lf\t= %8.4Lf\n", x, my_sqrtl(x));
#endif
            fflush(stdout);
            usleep(100);
        }
   // } while (getchar() != (int)'x');
    return 0;
}

