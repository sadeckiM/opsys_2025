#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <fcntl.h>

int main(void) {
	int fd[2];
	char * tekst = "Test tekstu dla potoku."; 
	int size = strlen(tekst);
	char inbuf[size];
	if(pipe(fd) == -1) {
		perror("pipe error\n");
		exit(-1);
	}
	int flags = fcntl(fd[0], F_GETFL, 0);
	fcntl(fd[0], F_SETFL, flags | O_NONBLOCK);
	
	write(fd[1], tekst, size);
	close(fd[1]);
	printf("Rodzic: zapisano dane do potoku.\n");
	//read(fd[0], inbuf, size);
	//printf("%s\n", inbuf);
	
	int pid = fork();
	if(pid < 0) {
		perror("fork problem\n");
		exit(-1);
	}

	if(pid == 0) {
		read(fd[0], inbuf, size);
		close(fd[0]);
		printf("Dziecko %d: %s\n", pid, inbuf);
		exit(0);
	}
}


