#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include<sys/wait.h> 

#define MAX 10

void ex1() {
    int ifd = open("notas_ppt.txt", O_RDONLY); // não quero muito estar a mexer em ficheiros do sistema :)
    int ofd = open("out/saida.txt", O_CREAT | O_TRUNC | O_WRONLY, 0666);
    int efd = open("out/erros.txt", O_CREAT | O_TRUNC | O_WRONLY, 0666);    
    dup2(ifd, 0); //stdin
    close(ifd);
    dup2(ofd, 1); //stdout
    close(ofd);
    dup2(efd, 2); //stderr
    close(efd);


    char*buf;
	buf=malloc(sizeof(char)*MAX);
	int n_read=read(0,buf,MAX);
	buf[MAX]='\0';
	write(1,buf,n_read);
}



void ex2() {
    int ifd = open("notas_ppt.txt", O_RDONLY); // não quero muito estar a mexer em ficheiros do sistema :)
    int ofd = open("out/saida.txt", O_CREAT | O_TRUNC | O_WRONLY, 0666);
    int efd = open("out/erros.txt", O_CREAT | O_TRUNC | O_WRONLY, 0666);    
    dup2(ifd, 0); //stdin
    close(ifd);
    dup2(ofd, 1); //stdout
    close(ofd);
    dup2(efd, 2); //stderr
    close(efd);

    pid_t t=fork(); // neste momento cria um novo processo filho, se o id for 0 está no filho, se não está no pai
    switch (t) {
        case 0:;
            char*buf;
	        buf=malloc(sizeof(char)*MAX);
	        int n_read=read(0,buf,MAX);
	        buf[MAX]='\0';
	        write(1,buf,n_read);
            _exit(0);
        case -1: 
            puts("Erro no fork\n");
            _exit(0);
        default : 
            wait(NULL);
    }
}

void ex2_b() {
    int ifd = open("notas_ppt.txt", O_RDONLY); // não quero muito estar a mexer em ficheiros do sistema :)
    int ofd = open("out/saida.txt", O_CREAT | O_TRUNC | O_WRONLY, 0666);
    int efd = open("out/erros.txt", O_CREAT | O_TRUNC | O_WRONLY, 0666);    
    dup2(ifd, 0); //stdin
    close(ifd);
    dup2(ofd, 1); //stdout
    close(ofd);
    dup2(efd, 2); //stderr
    close(efd);

    pid_t t=fork(); // neste momento cria um novo processo filho, se o id for 0 está no filho, se não está no pai
    switch (t) {
        case 0:
            execlp("cat","cat","notas_ppt.txt",NULL);
            _exit(0);
        case -1: 
            puts("Erro no fork\n");
            _exit(0);
        default : 
            wait(NULL);
    }
}


void ex3(){
    int ifd = open("notas_ppt.txt", O_RDONLY);
    int ofd = open("out/saida.txt", O_CREAT | O_TRUNC | O_WRONLY, 0666);
    int efd = open("out/erros.txt", O_CREAT | O_TRUNC | O_WRONLY, 0666);    
    dup2(ifd, 0); //stdin
    close(ifd);
    dup2(ofd, 1); //stdout
    close(ofd);
    dup2(efd, 2); //stderr
    close(efd);
    execl("/bin/wc","wc","notas_ppt.txt",NULL);
}

/*Escreva um programaredirque permita executar um comando, opcionalmente redireccionando a en-trada e/ou a sa ́ıda.
 O programa poder ́a ser invocado, com:redir [-i fich_entrada] [-o fich_saida] comando arg1 arg2 ...1*/
void ex4(int argc, char*argv[]){
    int i;
    for(i=1;i<argc;i++){
        if(argv[i][0]=='-'){
            if(strlen(argv[i])>1 && argv[i][1]=='i'){
                int ifd = open(argv[i+1],O_RDONLY);
                dup2(ifd,0);
                close(ifd);
            }else if(strlen(argv[i])>1 && argv[i][1]=='o'){
                int ofd = open(argv[i+1], O_CREAT | O_TRUNC | O_WRONLY, 0666);
                dup2(ofd,1);
                close(ofd);
            }
        }
        else{
            execvp(argv[i],argv+i); // Como a primeira entrada do array deve conter também o nome do executável não é preciso fazer i+1;
        }
    }
}





int main(int argc, char*argv[]){
    ex2_b();
    //ex4(argc,argv);
    return 0;
}

