#include <unistd.h>
#include <stdio.h>
#include <sys/wait.h>


// echo $PATH- no path estão declarados um conjunto de caminhos onde o programa pode procurar pelo executável

void ex1(){
    execl("/bin/ls","ls","-l",NULL);
    //execlp("ls","ls","-l",NULL); procura o executável no $PATH
    //char* execargs []= {"ls","-l",NULL};
    //execv("/bin/ls",execargs);
}

int ex2(){
    pid_t pid;
    if ((pid = fork()) == 0){
       execlp("ls","ls","-l",NULL);
       _exit(0); 
    
    }
    int x;
    wait(&x);  
    return 0;
}

void ex22(){
    pid_t pid;
    if ((pid = fork()) == 0){
       execlp("ls","ls","-l",NULL);   
    }
}

void ex3(int argc, char **argv){
    int i;
    for(i=1;i<argc;i++){
        printf("%s\n",argv[i]);
    }
}

void ex4(char **argv){
    execv("./ex3",argv);
}

void ex5(int argc,char **argv){
    int i;
    pid_t pid;
    for(i=1;i<argc;i++){
        if(pid =fork()==0){
            execlp(argv[i],argv[i],NULL);
            //_exit(0);
        }
    int status;
    //wait(&status);
    }
}

void ex6(int argc, char** argv){
    if(argc==2){
        execlp(argv[1],argv[1],NULL);
    }else if(argc>2){
        char* arglist[argc-2];
        int i =2;
        for(i;i<argc;i++){
            arglist[i-2] = argv[i];
        }
        execvp(argv[1],arglist);
    }
}



int main(int argc, char **argv){
    //ex1();
    //ex2();
    //ex3(argc,argv);
    //ex4(argv);
    ex6(argc,argv);
     //./ex6 /bin/ls -l
    return 0;
}