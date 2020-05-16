#include <unistd.h>
#include <fcntl.h>

#define MAX 100

int main(int argc, char *argv[]){
	char buf[MAX];
	int r = read(0,buf,MAX);
	write(1,buf,r);
	return 0;
}
