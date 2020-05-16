#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>

int ex1(){
    int fildes[2];
    int n;
    if(pipe(fildes)==-1) return -1;

    char buf[10];
    switch (fork())
    {
    case -1:
        perror("Error forking");
        exit(1);
        break;
    case 0:
        close(fildes[1]);
        while(n = read(fildes[0],buf,sizeof(buf))){
            write(1,buf,n); // escreve no ecâ o que leu
        };
        close(fildes[0]);
        _exit(0);
        break;
    default:
        close(fildes[0]);
        char text[]  = "Isto e o texto que vai ser escrito do pai para o filho";
        write(fildes[1],text,sizeof(text));
        close(fildes[1]);
        wait(NULL);
    }
    return 0;
}


int ex3(){
    int fildes[2];
    if(pipe(fildes)== -1) return -1;
    switch (fork())
    {
    case -1:
        perror("Error forking");
        exit(1);
        break;
    case 0:
        close(fildes[1]); // vai ler do descritor de escrita e escrever para o stdout
        dup2(fildes[0],0); // o wc lê do stdin, como é o fildes[0] que têm o texto, reorienta-se o IO
        close(fildes[0]);
        execlp("wc","wc",NULL);
        _exit(1);
    default:
        close(fildes[0]); // pai vai ler do stdin e escrever para o descritor de escrita, logo não precisa deste

        int n;
        char buf[10];
        while(n=read(0,buf,10)){
            write(fildes[1],buf,n);
        }
        close(fildes[1]);
        wait(NULL);
        break;
    }
}



// 2 processos- 1 pipe
//2 forks- 1 por casa processo
int ex4(){
    int fildes[2];
    if(pipe(fildes) == -1) return -1;
    // fork para o ls /etc
    switch (fork())
    {
    case -1:
        perror("Error forking");
        exit(1);
        break;
    case 0:
        close(fildes[0]);
        dup2(fildes[1],1); // o output do ls vai para o pipe de escrita
        close(fildes[1]);
        execlp("ls","ls","/etc",NULL);
        _exit(1); // caso teha corrido mal o exit fecha o processo e os descritores

    default:
    // fork para o wc
    close(fildes[1]); // fecha o descritor de escrita para o pai e filho logo
        if(fork()==0){
            dup2(fildes[0],0); // pois o wc lê do stdin
            execlp("wc","wc","-l",NULL);
            _exit(-1);
        }else{
            close(fildes[0]);// o fildes[1] foi fechado ali em cima l:90 
            // antes dos waits porque caso contrário causaria deadlock nos filhos que estariam À espera que todos os descritores  estivessem fechados
             wait(NULL);
             wait(NULL);
        }
        
        break;
    }
}

int ex4_2(){
    int fildes[2];
    if(pipe(fildes) == -1) return -1;
    // fork para o ls /etc
    pid_t pid;
    if((pid = fork())<0)
    {
        perror("Error forking");
        exit(1);
    }else if(pid==0){
        close(fildes[0]);
        dup2(fildes[1],1); // o output do ls vai para o pipe de escrita
        close(fildes[1]);
        execlp("ls","ls","/etc",NULL);
        _exit(1); // caso teha corrido mal o exit fecha o processo e os descritores
    }


    // pai
    // fork para o wc
    close(fildes[1]); // fecha o descritor de escrita para o pai e filho que irão resultar do novo fork
    if((pid = fork())==-1){
        perror("Error forking");
        exit(1);
    }else if(pid==0){
        dup2(fildes[0],0); // pois o wc lê do stdin
        execlp("wc","wc","-l",NULL);
        _exit(-1);
    }
    close(fildes[0]);// o fildes[1] foi fechado ali em cima l:90 , este não o podemos fechar antes pois é usado pelo filho
    // antes dos waits porque caso contrário causaria deadlock nos filhos que estariam À espera que todos os descritores  estivessem fechados
    wait(NULL);
    wait(NULL);
}



int ex5(){
    int N = 3; // número de pipes
    int fildes[N][2];
    // evitar criar os pipes todos de uma vez porque teria que estar afechar todos de uma vez

    if(pipe(fildes[0])==-1){
        perror("Error piping");
        return -1;
    }

    pid_t pid;
    if(fork()==0){
        close(fildes[0][0]);
        dup2(fildes[0][1],1);
        close(fildes[0][1]);
        execlp("grep","grep","-v","^#","/etc/passwd",NULL);
        _exit(1);
    }
    close(fildes[0][1]); // não precisamos mais do descritor de escrita do pai


    if(pipe(fildes[1])==-1){
        perror("Error piping");
        return -1;
    }
    if(fork()==0){
        close(fildes[1][0]);// não é preciso o descritor de leitura do pipe onde vamos escrever
        dup2(fildes[0][0],0);
        close(fildes[0][0]);
        dup2(fildes[1][1],1);
        close(fildes[1][1]);
        execlp("cut","cut","-f7", "-d:",NULL);
        _exit(1);
    }
    close(fildes[0][0]);// só foi fechado no filho
    close(fildes[1][1]);


    if(pipe(fildes[2])==-1){
        perror("Error piping");
        return -1;
    }
    if(fork()==0){
        close(fildes[2][0]);
        dup2(fildes[1][0],0);
        close(fildes[1][0]);
        dup2(fildes[2][1],1);
        close(fildes[2][1]);
        execlp("uniq","uniq",NULL);
        _exit(1);
    }
    close(fildes[1][0]);
    close(fildes[2][1]);


    if(fork()==0){
        dup2(fildes[2][0],0);
        close(fildes[2][0]);
        execlp("wc","wc","-l",NULL);
        _exit(1);
    }

    close(fildes[2][0]);

    //apenas para o processo pai não correr o prompt da shell antes do resto dos processos acabarem
    for(int i=0;i<3;i++){
        wait(NULL);
    }

}


int ex5_2(){
    int fildes[2][4];
    char ** commands[4];
    char *grep[5] = { "grep", "-v", "^#", "/etc/passwd", NULL };
    char *cut[4]  = { "cut", "-f7", "-d:", NULL };
    char *unic[2] = { "uniq", NULL };
    char *wc[3]   = { "wc", "-l", NULL };
    commands[0] = grep;
    commands[1] = cut;
    commands[2] = unic;
    commands[3] = wc;

    if(pipe(fildes[0])==-1){
        return -1;
    }
    if(fork()==0){
        close(fildes[0][0]);
        dup2(fildes[0][1],1);
        close(fildes[0][1]);
        execvp(commands[0][0],commands[0]);
        _exit(1);
    }
    close(fildes[0][1]);

    int i;
    for(i=1;i<3;i++){

        if(pipe(fildes[i])==-1){
            return -1;
        }
        if(fork()==0){
            close(fildes[i][0]);
            dup2(fildes[i-1][0],0);
            close(fildes[i-1][0]);
            dup2(fildes[i][1],1);
            close(fildes[i][1]);
            execvp(commands[i][0],commands[i]);
            _exit(1);
        }
        close(fildes[i-1][0]);
        close(fildes[i][1]);
    }

    if(fork()==0){
        dup2(fildes[i-1][0],0);
        close(fildes[i-1][0]);
        execvp(commands[i][0],commands[i]);
        _exit(1);
    }
    close(fildes[i][0]);
    int j;
    for(j=0;j<i;j++){
        wait(NULL);
    }


}



int main(){
    ex5_2();
    return 0;
}