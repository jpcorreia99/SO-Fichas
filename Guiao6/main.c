#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>

int ex1_1(){
    if(mkfifo("my_fifo",0666)<0){
        perror("mkfifo");
    }
}


// write to pipe
int ex1_2(){
    int fd;
    if((fd = open("my_fifo",O_WRONLY))<0){
        perror("open");
        exit(1);
    }
    printf("Open is done\n");

    char buf[100];
    int bytes_read=0;
    while((bytes_read = read(0,buf,100))>0){ //ler do stdin
        if(write(fd,buf,bytes_read)<0){
            perror("Write");
            exit(1);
        }
    }
    return 0;
}

//read e escreve para o stdout
int ex1_3(){
    int fd;
    if((fd = open("my_fifo",O_RDONLY))<0){
        perror("open");
        exit(1);
    }
    printf("Open is done\n");

    char buf[100];
    int bytes_read=0;
    while(bytes_read = read(fd,buf,100)){ 
        if(write(1,buf,bytes_read)<0){
            perror("Write");
            exit(1);
        }
    }
    return 0;
}


// escreve para o pipe mas usando o cat
int ex1_3_cat(){
    int fd;
    if((fd = open("my_fifo",O_WRONLY))<0){
        perror("open");
        exit(1);
    }
    printf("Open is done\n");


    int pid;
    if((pid=fork())==0){
        dup2(fd,1);
        close(fd);
        execlp("cat","cat",NULL);
        exit(1);
        
    }

    close(fd);
    wait(NULL);
    return 0;
}


int main(){
    // lembrar de correr no terminal unlink my_fifo
    ex1_3_cat();
    return 0;
}