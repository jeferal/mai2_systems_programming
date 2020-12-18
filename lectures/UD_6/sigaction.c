#include <sys/types.h>
#include <unistd.h>
#include <signal.h>
#include <string.h>
#include <stdio.h>
#include <math.h>

/*
gcc -o build/sigaction sigaction.c -lm
*/

char handmsg[] = "I found Ctrl-C\n";

struct sigaction act;

void handler_ctrl_c(int signo)
{
    write(STDERR_FILENO, handmsg, strlen(handmsg));
}

int catch_ctrl_c()
{
    act.sa_handler = handler_ctrl_c;
    sigemptyset(&act.sa_mask);
    act.sa_handler = 0;
    return sigaction(SIGINT, &act, NULL);
}

int ignore_ctrl_c()
{ 
    if (sigaction(SIGINT, NULL, &act) == -1){
        perror("Could not get old handler for SIGINT");
        return -1;
    } else if (act.sa_handler == handler_ctrl_c) {
        act.sa_handler = SIG_IGN;
 
    return sigaction(SIGINT, &act, NULL);
     }
}

int main()
{
    double y;

    catch_ctrl_c();
    fprintf(stderr, "CTRL-C will be catched for 10 sec\n");

    for(int i=0; i<100;i++){
        y = sin((double)i);
        //sleep(1);
    }
    ignore_ctrl_c();
    fprintf(stderr, "CTRL-C will be ignored for 10 sec\n");
    for(int i=0; i<100000000;i++){
        y = sin((double)i);
        //sleep(1);
    }
        
    fprintf (stderr, "Program ends\n");

    return 0;
}