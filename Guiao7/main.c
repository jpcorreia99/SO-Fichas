#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int ctr_c_counter=0;
int seconds=0;

void sigint_handler(int signum){
    ctr_c_counter++;
    printf("SIGINT recebido, Ctr+c pressionado %d vezes\n",ctr_c_counter);
    // fazer o tempo

}

void sigquit_handler(int signum){
    printf("SIGQUIT recebido, tempo passado %d\n",seconds);
}


void sigalrm_handler(int signum){
    printf("SIGALRM recebido\n");
    seconds++;
    alarm(1); // renova o alarme
}


int main(int argc, char* argv[]){
    if(signal(SIGINT,sigint_handler)==SIG_ERR){
        perror("sigint error");
        exit(1);
    }

    // ctr+'\'
    if(signal(SIGQUIT,sigquit_handler)==SIG_ERR){
        perror("sigquit error");
        exit(1);
    }
    
    if(signal(SIGALRM,sigalrm_handler)==SIG_ERR){
        perror("sigalrm error");
        exit(1);
    }

    // o SIGALRM mata o processo por default, mas posso mudar para contar segundos

    // problema que surgia se o alarm estivesse dentro do while: o ctr+c out ctr+\ quebram o pause, o que quebra o alarme pois é reiniciado
    alarm(1);
    while(1){
        pause(); // susprende o programa até receber um sinal (que devia ser o sigalrm)
        printf("Another interruption\n");
    }

}
