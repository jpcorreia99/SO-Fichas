#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#define BUF_SIZE 256


// typedef struct{...} Pessoa; Não é o apontador
// Pessoa p;
// read(fd, &p, sizeof(struct pessoa))

ssize_t readln(int fildes, void *buf, size_t nbyte){
    int i = 0;
    int readC;
    char c = 'a';
    char * buff = (char *) buf;

    while(c != '\n' && i < nbyte){
       readC = read(fildes, &c, 1);
       if (readC <= 0) return 0;
       buff[i] = c;
       i ++;
    }

    return (i);
}

int search_name(char* name){
    int fd = open("registo_pessoas.txt", O_RDONLY);
    char* buf = malloc(sizeof(char)*BUF_SIZE);
    char* name_tok = malloc(sizeof(char)*BUF_SIZE);
    int num_read;
    int total_read=0;
    //int n_lines;
    if(fd){
        while((num_read = readln(fd,buf,BUF_SIZE))!=0){
            //n_lines++;
            name_tok = strtok(buf,",");
            if(strcmp(name_tok,name)==0){
                close(fd);
                return total_read;
            }
            total_read+=num_read;
        }
    } 
    close(fd);
    return -1;
}

int change_entry(char* name, char* age){
    int fd = open("registo_pessoas.txt", O_RDWR);
    char* buf = malloc(sizeof(char)*BUF_SIZE);
    char* name_tok = malloc(sizeof(char)*BUF_SIZE);
    int num_read;
    //int n_lines;
    if(fd){
        while((num_read = readln(fd,buf,BUF_SIZE))!=0){
            //n_lines++;
            name_tok = strtok(buf,",");
            if(strcmp(name_tok,name)==0){
                lseek(fd,-(num_read-strlen(name_tok))+1,SEEK_CUR);
                write(fd,age,strlen(age));
                write(fd,"\n",1);
                break;
            }
        }
    }else{
        return 0;
    } 
    close(fd);
    return 1;
}

int write_person(char* name, char* age){
    int fd = open("registo_pessoas.txt", O_WRONLY | O_APPEND);
    if(fd){
        write(fd,name,strlen(name));
        write(fd,",",1);
        write(fd,age, strlen(age));
        write(fd,"\n",1);
    }else
    {
        return 0;
    } 
    close(fd);
    return 1;
} 

int main(int argc, char* argv[]){
    if(argc==4){
        if(strcmp("-i", argv[1])==0){
            write_person(argv[2], argv[3]);
        }else if(strcmp("-u",argv[1])==0){
            int res =change_entry(argv[2],argv[3]);
            if(res==0){printf("erro de escrita\n");}
        }
    }else{
        printf("Erro ao ler o ficheiro/ erro de argumentos\n");
    }
    //int line = search_name("guilherme");
    //printf("%d\n", line);

    return 0;
}

