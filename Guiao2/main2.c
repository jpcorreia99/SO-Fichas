#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <stdlib.h>


int ex1(){
    pid_t pid;
    pid = fork();
    switch (pid)
    {
    case -1:
        perror("Error forking");
        break;
    case 0:
        printf("Pid filho %d\n", getpid());
        break;
    default:
        printf("Pid pai:%d\n",getpid());
        break;
    }
}


int ex3(){
    int i=0;
    for(i=0;i<10;i++){
        switch (fork())
        {
        case -1:
            perror("Error forking");
            break;
        case 0:
            _exit(i);
        default: ;
            int status,s;
            int child_pid = wait(&status);
            if (WIFEXITED(status)) s=WEXITSTATUS(status);
            printf("Processo filho com o pid %d saiu com o código %d\n",child_pid,s);
            break;
        }
    }
}

int ex4(){
    int i;
    for(i=0;i<10;i++){
        if(fork()==0){
            printf("Pid: %d, Parent Pid %d\n",getpid(),getppid());
            _exit(i);
        }
    }

    int status,r;
    pid_t childProcessPid;
    for(i=0;i<10;i++){
        childProcessPid = wait(&status);
        if(WIFEXITED(status)){
            r = WEXITSTATUS(status);
            printf("Pid do filho %d, indice %d\n",childProcessPid,r);
        }
    }
    return 0;
}

int ex5(){
    int i;
    for(i=0;i<10;i++){
        pid_t pid;
        switch ((pid = fork()))
        {
        case -1:
            perror("Error forking");
            exit(1);
            break;
        case 0:
                printf("Forking\n");
                break;
        default: ;
            int status;
            int childpip = wait(&status);
            if(WIFEXITED(status)){
                int r =WEXITSTATUS(status);
                printf("[Pai]: Apanhei o filho com o pid %d e o status %d\n",childpip,r);
            }
            _exit(i);
        }
    }
    _exit(i);
    return 0;
}

int ex6(){
    int m [10][100] = {0};
    m[6][57]=1;
    m[5][12] =1;

    for(int i=0;i<10;i++){
        if(fork()==0){
            for(int j =0; j<100;j++){
                if(m[i][j]==1){
                   _exit(i); 
                }
            }
            _exit(0);
        }
    }

    int linhas[10] = {0};
    for(int i=0;i<10;i++){
        int status,index;
        wait(&status);
        if(WIFEXITED(status)){
            index = WEXITSTATUS(status);
            if(index!=0){
                linhas[index]=1;
            }
        }
    }
    for(int i=0;i<10;i++){
        printf("%d, ",linhas[i]);
    }
}

int main(){
    ex6();
}