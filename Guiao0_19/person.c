#include "person.h"
#include <stdlib.h>

Person new_person(char* name, int age){
    Person* p = malloc(sizeof(Person));
    p->age = age;
    p->name = name;

    return *p;
}

Person clone_person(Person *p){
    Person p2 = new_person(p->name, p->age);
}

void destroy_person(Person *p){
    free(p->name);
    free(p);
}

int person_age(Person *p){
    return p->age;
}

void person_change_age(Person *p, int age){
    p->age = age;
}
