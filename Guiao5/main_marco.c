#include <unistd.h>
#include <stdio.h>
#define MAX 4000


/*  EX 1
void main() {
    char buff[MAX];
    int p[2],n;

    pipe(p);

    //p[0] -----descritor de leitura
    //p[1] -----descritor de escritura

    if (fork()) {
        close(p[1])
        n=read(p[0],buff,MAX);
        write(0,buff,n);

    }
    closep(p[0]);
    sleep(5);
    write(p[1],"Ola meus amigos\n",16);

}
*/


/*  EX 2
void main() {
    char buff[MAX];
    int p[2],n;

    pipe(p);

    if (fork()) {
        close(p[1]);
        while ((n=read(p[0],buff,MAX))>0)
            write(1,buff,n);

    }
    close(p[0]);
    while((n=read(0,buff,MAX))>0) {
        write(p[1],buff,n);
    }
    close(p[1]);
}
*/

/*     EX 3 */
void main() {
    char buff[MAX];
    int p[2],n,wc,cena;

    pipe(p);

    if (!fork()) {
        close(p[1]);
        dup2(p[0],0);
        close(p[0]);
        execlp("wc","wc",NULL);
    }
    close(p[0]);
    while((n=read(0,buff,MAX))>0) {
        write(p[1],buff,n);
    }
    close(p[1]);
}



/*    EX 4
void main () {
    char buff[MAX];
    int p[2],n,cena;

    pipe(p);

    if (fork()) {
        close(p[1]);
        dup2(p[0],0);
        close (p[0]);
        execlp("wc","wc","-l",NULL);
    }
    close(p[0]);
    dup2(p[1],1);
    close (p[1]);
    execlp("ls","ls","/etc",NULL);
}

*/

/* EX5(esta muito complicado de perceber da para usar apenas um descritor) 

void main () {
    char buff[MAX];
    int p[2],aux1[2],n,cena;
    pipe(p);
    if (!fork()) {
        pipe(aux1);
        if (!fork()) {
            pipe(p);
            if (!fork()) {
                close(p[1]);
                dup2(p[0],0);
                close(p[0]);
                execlp("wc","wc","-l",NULL);
            }
            
            close(aux1[0]);
            dup2(aux1[1],1);
            close(aux1[1]);
            execlp("uniq","uniq",NULL);
        }
        close(aux1[0]);
        dup2(aux1[1],1);
        close(aux1[1]);
        close(p[1]);
        dup2(p[0],0);
        close(p[0]);
        execlp("cut","cut","-f7","-d:",NULL);
    }
    close(p[0]);
    dup2(p[1],1);
    close(p[1]);
    execlp("grep","grep","-v","^#","/etc/passwd",NULL);

}

*/