#include <unistd.h>
#include <stdio.h>
#include <signal.h>

/*
gcc -o build/sigsuspend sigsuspend.c -lm
*/

char handmsg1[] = "Signal catched\n";
char handmsg2[] = "15 sec. timeout expired.\n";
struct sigaction act;

int signum, signal_received = 0;

void handler(int signo)
{ 
    if (signo!=SIGALRM)
        write(STDERR_FILENO, handmsg1, strlen(handmsg1));
    else{
        signal_received=1;
        write(STDERR_FILENO, handmsg2, strlen(handmsg2));
    }
}

int main(int argc, char *argv[])
{
    sigset_t sigset;

    if (argc != 2) 
        fprintf (stderr, "Usage: %s signo\n", argv[0]);
    
    signum=atoi(argv[1]);

    act.sa_handler = handler;

    sigfillset(&act.sa_mask);

    act.sa_flags = 0;

    sigaction(SIGALRM, &act, NULL);
    sigaction(signum, &act, NULL);

    sigfillset(&sigset);
    sigdelset(&sigset, signum);
    sigdelset(&sigset, SIGALRM);

    fprintf (stderr, "Waiting for 15 sec occurrences of signal n: %s\n", argv[1]);
    alarm(15);
    while(signal_received == 0) 
        sigsuspend(&sigset);
    fprintf (stderr, "Program terminated\n", argv[1]);
}