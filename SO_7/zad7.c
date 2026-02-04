#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <string.h>

#define SIZE 1024

int main(void) {
	pid_t cpid;
	int fd[2];
	ssize_t num_bytes;

	char buf[SIZE];

	if(pipe(fd) == -1) {
		perror("pipe");
		exit(EXIT_FAILURE);
	}
	
	cpid = fork();

	if(cpid == -1) {
		perror("fork");
		exit(EXIT_FAILURE);
	}

	if(cpid == 0) {
		dup2(fd[1], STDOUT_FILENO);
		close(fd[0]);
		if(execlp("cal", "cal", NULL) == -1) {
			perror("execlp");
			exit(EXIT_FAILURE);
		}
	} else {
		close(fd[1]);
		num_bytes = read(fd[0], buf, SIZE - 1);

		if(num_bytes > 0) {
			buf[num_bytes] = '\0';
			printf("Odebrano:\n\n %s", buf);
		} else
			printf("Nie odebrano danych.\n");

		close(fd[0]);
		wait(NULL);
		exit(EXIT_SUCCESS);
	}

	return 0;
}
