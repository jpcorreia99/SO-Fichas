#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>


typedef struct pessoa{
    int age;
    char name[50];
}Person;



int add_person(int fd, char *name, int age)
{
    Person p;
    
    strcpy(p.name, name);
    p.age = age;
    
    write(fd, &p, sizeof(Person));
    
    int index = lseek(fd, 0, SEEK_END) / sizeof(Person) - 1;
    
    return index;
}

int change_age(int fd, char *name, int age)
{
    int n;
    char buf[1000];
    
    do {
        n = read(fd, buf, sizeof(Person));
    } while (n && strcmp(buf, name));
    
    if (!n)
        return -1;
    
    Person p;
    
    strcpy(p.name, name);
    p.age = age;
    
    lseek(fd, -sizeof(Person), SEEK_CUR);
    write(fd, &p, sizeof(Person));
    
    return 0;
}

int change_age_index(int fd, int index, int age)
{
    Person p;
    
    lseek(fd, index * sizeof(Person), SEEK_SET);
    read(fd, &p, sizeof(Person));
    
    p.age = age;
    
    lseek(fd, -sizeof(Person), SEEK_CUR);
    write(fd, &p, sizeof(Person));
    
    return 0;
}

int changePersonAge(int fd, long pos, int age){
    Person p;


    int seek_res = lseek(fd, pos*sizeof(Person), SEEK_SET);
    if(seek_res<0){
        printf("LSEEK error\n");
        return -1;
    }
    printf("\n%d\n",seek_res);
    
    int bytes_read = read(fd,&p, sizeof(Person));
    if(bytes_read<0){
        printf("Read error\n");
        return -1;
    }

    printf("Read %s,%d\n",p.name,p.age);
    return 0;   
}

int main(){
    int fd = open("registo_pessoas.txt", O_RDWR);
    printf("%d\n",changePersonAge(fd,2,24));
    return 0;
}

