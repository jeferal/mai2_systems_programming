#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <signal.h>

/*
gcc -o build/sigprocmask sigprocmask.c -lm
*/

int main(int argc, char* argv[])
{
    double y;
    sigset_t intmask;
    int repeat_factor;

    if(argc!=2)
    {
        fprintf(stderr, "Usage: %s repeat_factor\n", argv[0]);
        return -1;
    }

    repeat_factor = 1000000*atoi(argv[1]);
    sigemptyset(&intmask);
    sigaddset(&intmask, SIGINT);

    for(;;)
    {
        sigprocmask(SIG_BLOCK, &intmask, NULL);
        fprintf(stderr, "SIGINT signal blocked\n");
        for(int i=0; i<repeat_factor; i++)
            y=sin((double)i);
        fprintf(stderr, "Blocked calculation is finished\n");

        sigprocmask(SIG_UNBLOCK, &intmask, NULL);
        fprintf(stderr, "SIGINT signal unblocked\n");

        for(int i=0; i<repeat_factor; i++)
            y=sin((double)i);
        fprintf(stderr, "Unblocked calculation is finished\n");
    }

    return 0;
}