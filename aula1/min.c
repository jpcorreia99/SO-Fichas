#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>


int main(){
	int min=1000,x,n;
	char*buf;
	buf=malloc(sizeof(char)*4);
	n=read(0,buf,4);
	buf[3]='\0';
	while(n!=1 && (buf[0]>48 && buf[0]<57)){
		x=atoi(buf);
		if(x<min){
			min=x;
		}
		n=read(0,buf,4);
		buf[3]='\0';
	}
	
	printf("%d\n",min);
	return 0;
}


