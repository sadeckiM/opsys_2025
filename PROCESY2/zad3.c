#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <string.h>

char *createName(pid_t pid);

int main(void) {
    srand(time(NULL));
    size_t size = 1000000 * sizeof(float);
    float * tab = (float* )malloc(size);

    if(tab == NULL) {
        perror("Blad alokacji");
        exit(-1);
    }

    int initial = 0;
    int lim = 99999;
    char *f_names[10];
    float *ptr = tab;
    float total = 0.0f;
    for(int i = 0; i < 1000000; i++)
        *ptr++ = ((float)rand() / RAND_MAX) * 2 - 1;

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
            float sum = 0.0f;
            for(int j = initial; j < lim; j++)
                sum += tab[j];
            printf("Suma dziecka (%d %d): %f\n", initial, lim, sum);
            char * name = createName(getpid());
            FILE *file = fopen(name, "w");
            if(file) {
                fprintf(file, "%f\n", sum);
                fclose(file);
                free(name);
            }
            exit(0);
        }
        else
            f_names[i] = createName(status);
    }

    for(int i = 0; i < 10; i++)
        wait(NULL);

    for(int i = 0; i < 10; i++) {
        FILE * f = fopen(f_names[i], "r");

        if(f == NULL) {
            perror("Blad otwarcia pliku.");
            exit(-1);
        }
        float num;
        if(fscanf(f, "%f", &num) == 1)
            total += num;
        else {
            perror("Blad odczytu z pliku");
            exit(-1);
        }
        fclose(f);
        free(f_names[i]);

    }
    printf("Suma rodzica: %f\n", total);
    free(tab);
    return 0;
}

char * createName(pid_t pid) {
    char *pref = "temp/sum";
    char *suff = ".txt";
    char num[16];

    snprintf(num, sizeof(num), "%d", pid);

    char * res = (char* )malloc(strlen(num) + strlen(pref) + strlen(suff) + 1);
    if(!res) {
        perror("Blad alokacji dla nazwy");
        exit(-1);
    }
    strcpy(res, pref);
    strcat(res, num);
    strcat(res, suff);

    return res;
}