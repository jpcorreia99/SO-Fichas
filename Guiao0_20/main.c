#include "vector.h"
#include <stdlib.h>
#include <stdio.h>

int vector2[] = {0,1,2,3,4,5,6};

int main(){
    int *vector1;
    vector1 = malloc(sizeof(int)*10);
    fill(vector1,10,1);
    int i;
    for(i=0;i<10;i++){
        printf("%d,", vector1[i]);
    }
    printf("\n");

    printf("%d\n", find(vector2,7,2));
    return 0;
}