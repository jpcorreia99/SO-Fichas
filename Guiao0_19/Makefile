################### Makefile ####################
#everytime one of these changes, recompile the files

#if we call make all, it will compile everything
all: main


main: main.o person.o 
	gcc main.o person.o -o main

#just compile to a .o file
main.o: main.c 
	gcc -c main.c 

person.o: person.c
	gcc -c person.c

#delete all .o files
clean:
	rm *.o 
