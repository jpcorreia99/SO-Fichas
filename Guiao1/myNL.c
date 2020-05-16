#include <unistd.h>
#include <fcntl.h>
int main(){

    open("origem.txt",O_RDONLY);\
    return 1;
}