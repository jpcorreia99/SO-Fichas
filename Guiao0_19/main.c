#include "person.h"
#include <stdlib.h>
#include <stdio.h>

// gcc -o main.exe main.c person.c


int main(){
    Person p = new_person("joão",20);
    printf("Name: %s\n", p.name);
    printf("Age: %d\n", person_age(&p));

    Person p2 = clone_person(&p);
    person_change_age(&p2, 21);
    printf("Name 2: %s\n", p2.name);
    printf("Age 2: %d\n", p2.age);
}
