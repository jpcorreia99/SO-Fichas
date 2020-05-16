#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>


int main(){
    int log_fd = -1;
    // nota: este não vai bloquear pois está a ler um ficheiro normal
    if((log_fd = open("log.txt", O_CREAT| O_TRUNC | O_WRONLY,0666))<0){
        perror("open log");
        exit(1);
    }

    int fifo_fd=-1;
    while(fifo_fd = open("my_fifo",O_RDONLY)){ // para ir lendo continuamente
        printf("fifo is open\n");
        int bytes_read=0;
        char buf[100];
        while((bytes_read=read(fifo_fd, buf,100))>0){
            write(log_fd,buf,bytes_read);
        }
        close(fifo_fd);
    }



    close(log_fd);

    return 0;
}