
#include <stdio.h>
#include <stdlib.h>
#include "cutil.h"
#include <string.h>
#include "vmcutil.h"

//static ccontext_t context = {0};


const char *teststrs[] = {
    "One",
    "Two",
    "Three",
};


void server_print_list( char **strs, int count)
{
#ifdef DEFAULT_CLIENT_CONTEXT
    DCC_START_CALL(65, 2, sizeof(strs) + sizeof(count) + (count + 1)*sizeof(strs) +count*20 + 4);
    DCC_ADD_ARG(strs, 2);
    DCC_ADD_ARG(count, 0);
    DCC_ARG_OVER();
    DCC_ADD_MEM_ARR(strs, count, ((int *)NULL), 0);
    DCC_RET_ONLY();
    DCC_END_CALL();
#endif
}

char *my_reverse(char *x, int begin, int end)
{
#ifdef DEFAULT_CLIENT_CONTEXT
    DCC_START_CALL(68, 2, sizeof(x) + sizeof(begin) + sizeof(end) + end + 4);
    DCC_ADD_ARG(x, 1);
    DCC_ADD_ARG(begin, 0);
    DCC_ADD_ARG(end, 0);
    DCC_ARG_OVER();
    DCC_ADD_APTR_MEM(x, end + 1, 0);
    DCC_RET_ONLY();
    DCC_UPDATE_NON_CONST_PTR_ON_RET(x, end, 0);
    DCC_END_CALL();
#endif
    return x;
}

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


void *threadfunc(void *ctx)
{
    while(1) {
//        printf("Comparision result: %d\n", my_strcmp(str1, str2));
        fflush(stdout);
        usleep(100);
    }
}


int main(int argc, char **argv)
{
    long double t1, t2;
    char *mem = NULL;
    char *end = NULL;
    int size = (argc > 1)? atoi(argv[1]): 100;
    pthread_t thread;

    mem = malloc(size);
    if (!mem) return -1;
    end = mem+size -1;
    do {
    strcpy(mem, "Jagdish Prajapati");
    *(end) = '\0';
    *(end - 1) = 'j';
    *(end - 2) = 'p';
    printf("size = %d\n", size);
    printf("%s\n", mem);
    printf("%s\n", (end - 2));
    t1 = get_millisecond_time();
    my_reverse(mem,0,size - 1);
    t2 = get_millisecond_time();
    printf("Time Taken in call of my_reverse function with memory exchange of %d bytes : %Lf ms\n", size, t2-t1);
    printf("After reverse: %s\n", mem+1);
    printf("end After reverse: %s\n", end - 10 );

    server_print_list((char **)teststrs, sizeof(teststrs)/ sizeof(char *));
    } while (getchar() != (int)'x');
    return 0;
}

