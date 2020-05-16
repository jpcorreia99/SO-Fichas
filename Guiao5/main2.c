#include <unistd.h>

int ex1(){
    int fildes[2];
    if(pipe(fildes)==-1){
        return -1;
    }

    if(fork()==0){
        close(fildes[1]);
        char buf[10];
        int n_read;
        while(n_read = read(fildes[0],buf,10)){
            write(1,buf,n_read);
        }   
        close(fildes[0]);
        _exit(0);
    }else{
        close(fildes[0]);
        char buf[] = "Estou a escrever isto aqui no pai";
        write(fildes[1],buf,sizeof(buf));
        close(fildes[1]);
    }
}

int main(){
    ex1();
    return 0;
}