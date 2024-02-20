#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>  
#include <pthread.h> 
#include <sys/wait.h>
#include <signal.h>

void handle_sigint(int sig) 
{ 
    printf("Recibida señal SIGINT\n"); 
    exit(0);
} 

int main(){
    signal(SIGINT, handle_sigint); 

    char command[100];
    
    int procesoHijo1 = fork();

    if(procesoHijo1 == 0){

        char *argv[] = {NULL};
        execv("./proceso", argv);
    
    } else {
        int procesoHijo2 = fork();
        
        if(procesoHijo2 == 0){
            char *argv[] = {NULL};
            execv("./proceso", argv);
        } else {

            sprintf(command, "%s %d %d %s", "sudo stap trace.stp ", procesoHijo1, procesoHijo2, " > syscall.log");
            system(command);
            wait(NULL);
            wait(NULL);
        }
    }
    return 0;
}