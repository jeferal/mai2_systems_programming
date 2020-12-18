//Ejemplo.c
#include <unistd.h>
#include <stdio.h>

int main(int argc, char *argv[]) {
    
    execl("ls", "ls", "-la", NULL);
    //Devería añadirse el path!!!
    //execl("/bin/ls", "ls", "-la", NULL);
    printf(" System call failure \n");
    execlp("ls", "ls", "-la", NULL);

}   // end main()