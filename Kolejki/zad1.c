#include <mqueue.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>

#define MAX 64

void printFile(const char* fileName) {
	fflush(stdout);
	pid_t pid = fork();
	char path[MAX];
	if(pid == -1) {
		perror("fork");
		exit(-1);
	}
	if(pid == 0) {
		sprintf(path, "/proc/sys/fs/mqueue/%s", fileName);
		execlp("cat", "cat", path, NULL);

	} else if(pid > 0)
		wait(NULL);
	else {
		perror("execlp");
		exit(-1);
	}
}

int main(void) {
	printf("Maksymalna liczba wiadomosci: ");
	printFile("msg_max");
	printf("Liczba wiadomosci: ");
	printFile("msg_default");
	printf("Rozmiar wiadomosci: ");
	printFile("msgsize_default");
	printf("Maksymalny rozmiar wiadomosci: ");
	printFile("msgsize_max");
	printf("Maksymalna liczba kolejek: ");
	printFile("queues_max");
	return 0;
}
