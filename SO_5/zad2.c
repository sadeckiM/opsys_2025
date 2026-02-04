#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main(void) {
    srand(time(NULL));
    size_t size = 1000000 * sizeof(int);
    int * tab = (int* )malloc(size);

    if(tab == NULL) {
        perror("blad alokacji");
        exit(-1);
    }

    int initial = 0;
    int lim = 99999;
    int sum_p = 0;
    int *ptr = tab;
    for(int i = 0; i < 1000000; i++)
        *ptr++ = rand() % 100;

    for(int i = 0; i < 10; i++) {
        pid_t status = fork();
        initial = (i * 100000);
        lim = initial + 99999;

        if(status == -1) {
            perror("Fork: ");
            printf("nr %d\n", status);
            exit(-1);
        }
        if(status == 0) {
            int sum = 0;
            for(int j = initial; j < lim; j++)
                sum += tab[j];
            int mean = sum / 100000;
            printf("Srednia (%d %d): %d\n", initial, lim, mean);
            exit(mean);
        }
    }

    int total = 0;
    for(int i = 0; i < 10; i++) {
        int status;
        wait(&status);
        if(WIFEXITED(status)) {
            total += WIFEXITED(status);
        }
    }

    printf("Srednia rodzica: %d\n", total / 10);
    free(tab);
    return 0;
}