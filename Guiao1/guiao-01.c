#include <sys/types.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX_BUF 4096
#define BUF_SIZE 256
#define READ_BUFFER char[256]
#define READ_BUFFER_END
#define READ_BUFFER_POS

// ananunes@di.uminho.pt

//Nota, evitar as variáveis globais e trocá-las por um buffer local

/* Como fazer a readline, há um buffer global para onde é lida o texto,
há também uma variável global read_buffer_pos que é o indice onde se contaq qual indice estamos a ler
há também um read_buffer_end, se eles coincidirem, faço um read 
*/


int cp(int argc, char *argv[]){
    if(argc==3){
        char* origem = argv[1];

        char* destino = argv[2];
        int fd_origem, fd_destino;
        if((fd_origem = open(origem,O_RDONLY))==-1){
            perror("open");
            return -1;
        }
        if((fd_destino = open(destino, O_WRONLY|O_CREAT,0600))==-1){ //o append vai adicionando ao ficheiro
            perror("open");
            return -1;
        }
        int num_read;
        char *buf = malloc(sizeof(char)*MAX_BUF);
    
        while((num_read=read(fd_origem,buf, MAX_BUF))>0)
        {
            write(fd_destino, buf,num_read);
        } 

        close(fd_origem);
        close(fd_destino);

    }
    else
    {
        printf("instructions unclear\n");
    }
}

int getchar_(int fild,  void* b){
        int res = read(fild,b,1);
        return res;
}

int getbufofchars(int fild, void* buf, size_t size){
        int res = read(fild,buf,size);
        int i;
        for(i=0;i<res && ((char*)buf)[i]!='\n';i++);
        return i;
}

ssize_t readln(int fd, void *buf, size_t size){
    int total_read=0;
    int read=0;
    char* buffer = malloc(sizeof(char)*BUF_SIZE);
    while (total_read <size)
    {   
        read = getbufofchars(fd,buffer,BUF_SIZE);
        strncpy(((char*)buf)+total_read, buffer, read);
        total_read+=read;
        printf("\n%d characters\n",total_read);
        if(((char*) buf)[total_read]=='\n'){
            return total_read+1;
        }
        if(read<BUF_SIZE){
            break;
        }
    }

 return (total_read==size)?-1:total_read;   
}

int readC(int fd, char* c){
    return read(fd,c,1);
}

ssize_t readlnC(int fildes, void *buf, size_t nbyte){
    int i = 0;
    int readCount;
    char c = 'a';
    char * buff = (char *) buf;

    while(c != '\n' && i < nbyte){
       readCount = readC(fildes, &c);
       if (readCount <= 0) return 0;
       buff[i] = c;
       i ++;
    }

    return (i);
}

void myNL(int fd, char* buf){
    int num_read;
    char index = 0;
    while((num_read = readlnC(fd,buf,MAX_BUF))>0){
        index++;
        char* numC = malloc(sizeof(char)*12);
        sprintf(numC,"%d  ",index);; 
        write(1,strcat(numC,buf),num_read+12);
        free(numC);
    }

}



int main(int argc, char *argv[]){
    int fd_origem;
    char* buf = malloc(sizeof(char)*MAX_BUF);
    if((fd_origem = open("origem.txt",O_RDONLY))!=-1){
        /*int num_read = readln(fd_origem,buf, MAX_BUF);
        printf("%s",buf);
        printf("Num read: %d\n", num_read);*/
        myNL(fd_origem,buf);
    }else {
        printf("Ficheiro não existe");
        return -1;
    }
    free(buf);
}



