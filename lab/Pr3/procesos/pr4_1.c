#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>

int main(int argc, char *argv[]){
    printf("Soy el proceso %ld antes de crear otro proceso\n", (long)getpid());
    fork();
    printf("Soy el proceso %ld y mi padre es %ld\n",(long)getpid(),
    (long)getppid());
    sleep(15);
    return 0;
}