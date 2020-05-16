#include <signal.h>
#include <stdio.h>

void sig_handler(int signum){
    printf("Recebi %d sinal\n",signum);
}

int main(){
 if(signal(SIGINT,sig_handler)==SIG_ERR){
     perror("signal");
     exit(1);
 }

 while(1){
     pause();
 }
}