#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main(void) {
    srand(time(NULL));

    int a = rand() % 11;
    int b = rand() % 11 + 20;

    pid_t res = fork();

    if(res == -1) {
        perror("Fork: ");
        printf("nr %d", res);
        exit(-1);
    }

    if(res == 0) {
        int sum_child = a + b;
        printf("Liczby to %d %d, a suma %d\n", a, b, sum_child);
        exit(sum_child);
    }
    else {
        wait(&res);

        if(WEXITSTATUS(res))
            printf("Status zakonczenia: %d\n", WEXITSTATUS(res));
        return 0;
    }
}