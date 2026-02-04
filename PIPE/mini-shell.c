#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/wait.h>

#define SIZE 64
#define OSIZE 1024

typedef struct {
	char **left;
	char **right;
} split_t;

void printInstruction(void);
char ** tokenize(char tab[], int pos);
void runHandler(char ** args);
void execRun(pid_t pid, char **args, int fd[]);
void execRedirect(pid_t pid, char **left, char **right);
void redirectHandler(char ** left, char ** right);
void flush_stdin(void);
int read_stdin(char tab[]);
split_t adv_tokenize(char tab[]);
char ** alloc_tab(void);
void execPipe(int fd[], int fd_in, int fd_out, char ** tab);

int main(void) {
	printf("Mini-shell. Format polecen:\n");
	printInstruction();
	char buf[SIZE] = {0};

	while(buf[0] != 'q') {
		read_stdin(buf);
		if(buf[0] == 'q')
			break;

		if(strncmp(buf, "run", 3) == 0) {
			char** buf_tok = tokenize(buf, 3);
			runHandler(buf_tok);
			free(buf_tok);
		}
		else if(strncmp(buf, "redirect", 8) == 0) {
			split_t s = adv_tokenize(buf);
			redirectHandler(s.left, s.right);
			free(s.left);

		} else {
			printf("Niepoprawna forma. Uzyj:\n");
			printInstruction();
		}
	}
	printf("Koniec.\n");
	return 0;
}

void printInstruction(void) {
	printf("run [komenda], redirect [komenda1] to [komenda2], q - wyjscie.\n");
}

void flush_stdin(void) {
	int c;
	while((c = getchar()) != '\n' && c != EOF);
}

char ** tokenize(char tab[], int pos) {
	char* cmd = tab + pos;
	while(*cmd == ' ') cmd++;

	char **argv = alloc_tab();
	int i = 0;
	char* token = strtok(cmd, " ");

	while(token != NULL && i < SIZE - 2) {
		argv[i++] = token;
		token = strtok(NULL, " ");
	}
	argv[i] = NULL;
	
	return argv;
}

split_t adv_tokenize(char tab[]) {
	char ** argv = tokenize(tab, 8);
	char ** sep = NULL;

	for(int i = 0; argv[i] != NULL; ++i) {
		if(strcmp(argv[i], "to") == 0) {
			sep = &argv[i];
			break;
		}
	}

	split_t res;

	if(sep != NULL) {
		*sep = NULL;
		res.left = argv;
		res.right = sep + 1;
	} else {
		res.left = argv;
		res.right = NULL;
	}

	return res;
}

char ** alloc_tab(void) {
	char **argv = (char**) malloc(SIZE * sizeof(char*));
	if(!argv) {
		perror("malloc");
		exit(EXIT_FAILURE);
	}
	return argv;
}

void runHandler(char ** args) {
	int fd[2];
	char buf[OSIZE];

	if(pipe(fd) == -1) {
		perror("pipe");
		exit(EXIT_FAILURE);
	}

	execPipe(fd, -1, 1, args);
	close(fd[1]);

	ssize_t num = read(fd[0], buf, OSIZE - 1);
	if(num > 0) {
		buf[num] = '\0';
		printf("%s", buf);
	}
	close(fd[0]);

	wait(NULL);
}

void execRedirect(pid_t pid, char **left, char **right) {

	ssize_t num_bytes;
	char buf[OSIZE];

	int fd[2];
	if(pipe(fd) == -1) {
		perror("pipe");
		exit(EXIT_FAILURE);
	}

	execPipe(fd, -1, 1, left);
	execPipe(fd, 0, -1, right);

	close(fd[0]);
	close(fd[1]);
	wait(NULL);
	wait(NULL);
}

void execPipe(int fd[], int fd_in, int fd_out, char ** tab) {
	pid_t pid = fork();
	if(pid == 0) {
		if(fd_in != -1) {
			dup2(fd[fd_in], STDIN_FILENO);
			close(fd[fd_in]);
		}
			
		if(fd_out != -1) {
			dup2(fd[fd_out], STDOUT_FILENO);
			close(fd[fd_out]);
		}

		close(fd[0]);
		close(fd[1]);

		execvp(tab[0], tab);
		perror("exec");
		exit(EXIT_FAILURE);
	}
}

void redirectHandler(char ** left, char ** right) {
	if(right == NULL) {
		printf("Nie Podano drugiego argumentu.\n");
		return;
	}

	int fd[2];

	if(pipe(fd) == -1) {
		perror("pipe");
		exit(EXIT_FAILURE);
	}

	execPipe(fd, -1, 1, left);
	execPipe(fd, 0, -1, right);

	close(fd[0]);
	close(fd[1]);

	wait(NULL);
	wait(NULL);
}

int read_stdin(char tab[]) {
	int i = 0, c;
	for(i = 0; i < SIZE - 1; ++i) {
		c = getchar();
		if(c == '\n' || c == EOF)
			break;
		tab[i] = (char)c;
	}
	tab[i] = '\0';
	if(c != '\n' && c != EOF)
		flush_stdin();
	return i;
}

