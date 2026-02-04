#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>

#ifndef SIZE
#define SIZE 8000
#endif

int main(void) {
	
	int fd[2];
	int inbuf[SIZE];

	if(pipe(fd) == -1) {
		perror("pipe problem\n");
		exit(-1);
	}
	
	int pid = fork();

	if(pid < 0) {
		perror("fork problem\n");
		exit(-1);
	}

	if(pid == 0) {
		read(fd[0], inbuf, SIZE);
		//TODO sprawdzać, czy read zwrocil tyle co SIZE
		printf("%s\n", _strupr(inbuf));
		exit(0);
	}

}
