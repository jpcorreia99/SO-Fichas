#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <stdlib.h>



//ex1

void ex1 () {
    pid_t t;
    t=getpid();
    printf("%d\n",t);
    t=getppid();
    printf("%d\n",t);
}


//ex2


void ex2() {
    pid_t t=fork(); // neste momento cria um novo processo filho, se o id for 0 está no filho, se não está no pai
    switch (t) {
        case 0 :
            printf("\n\nSou Filho\nO meu id é: %d\nO id do meu pai é: %d\n",getpid(),getppid());
            exit(0);
        case -1: 
            puts("Erro\n");
            exit(0);
        default : 
            printf("\n\nSou Pai\nO meu id é: %d\nO id do meu filho é: %d\nO id do meu pai é: %d\n",getpid(),t,getppid());
            exit(0);
    }
}



//ex3

void ex3(){
    int i=0,status,s;
    pid_t pid,childpid;
    for(i=0;i<10;i++){
        pid = fork();
        if(pid==0){
            _exit(i+1);
        }if(pid==-1){
            printf("Errooo");
            _exit(-1);
        }else{
            childpid = wait(&status);
            if (WIFEXITED(status)) s=WEXITSTATUS(status); //wifeexisted- devolve algo !0 se o status tiver vindo de um child process
            printf("pid filho: %d, pid pai %d, ordem filho %d \n", childpid, getpid(),s);
        }
    }
}


int ex3_2 () {
    int r,s,i;
    pid_t t;
    for (i=0;i<10;++i) {
        t=fork();
        switch (t) {
            case 0: 
                printf("\n\nSou Filho\nO meu id é: %d\nO id do meu pai é: %d\n",getpid(),getppid());
                _exit(i+1);
            case -1:
                printf("Errooo");
                _exit(-1);
            default :
                t=wait(&r);
                if (WIFEXITED(r)) s=WEXITSTATUS(r);
                printf("\n\nSou Pai\nMorreu Filho com id: %d e indice: %d\n",t,s);
        }
    }
}


// ter um processo pai e 10 processos filho 
// um ciclo onde se criam todos
//um ciclo onde se fecham todos

void ex4(){
    int i;
    pid_t pid;
    for (i=0;i<10;++i) {
        pid=fork();
        if(pid==0){
            printf("PID: %d\n", getpid());
            printf("Parent PID: %d\n", getppid());
            _exit(i+1);
        }
    }
    
    int r,s;
    pid_t t;
    for(i=1;i<=10;i++){
        t=wait(&r);
        if (WIFEXITED(r)) s=WEXITSTATUS(r);
        printf("\n\nSou Pai\nMorreu Filho com id: %d e indice: %d\n",t,s);
    }
}

//cntr+Z depois para congelar os processos
// pstree -c $$
void ex5(){
 int status; 
 pid_t pid;   
    for(int i=0;i<10;i++){     
          switch(pid=fork()){     
              case -1:    
                  perror("fork");     
              case 0:    
                  printf("forking\n");    
                  break;    
              default:      
                // espera que o filho acabe
                // morre        
                  wait(&status);                                
                  printf("<dad> son's status: %d\n",status);    
                  _exit(i);    
                  break;    
          }    
      }       
      sleep(1000);
      // é o primeiro exit a ser ativado    
      _exit(10);
}   

//6 e 7 ao mesmo tempo
void ex6(){
    int m[10][500] = {0};
    m[3][40]=2;
    m[1][97]=2;
    m[9][1]=2;
    m[5][80]=2;
    int i,j,linha,status;
    pid_t pid;
    for(i=0;i<10;i++){
        pid=fork();
        if(pid==0){
            for(j=0;j<500;j++){
                if(m[i][j]==2) _exit(i);
            }
            _exit(0);
        }
    }

    int res[10]={0};
    for(i=0;i<10;i++){
        wait(&status);
        if (WIFEXITED(status)) linha=WEXITSTATUS(status);
        if(linha!=0) res[linha]=1;
    }

    for(i=0;i<10;i++){
        if(res[i]) printf("Linha %d\n",i);
    }

}

int main(){

    ex5();
    return 0;
}