#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>

/***************************Przyklad*************
int main(void) {

    for(int i = 0; i < 5; ++i) {
        int res = fork();
        if(res == -1) {
            perror("Fork: ");
            printf("nr %d", res);
            exit(1);
        }
        if(res == 0) {
           printf("Jestem dzieckiem.\n");
           exit(0);
        }
        /*else {
            printf("Jestem rodziem.\n");
        }
    }

    return 0;
}*/

/************ZAD 2**********
int main(void) {

    printf("Poczatek\n");
    int res = fork();
    if(res == -1) {
        perror("Fork: ");
        exit(1);
    }
    else if(res != 0) {
        printf("Koniec\n");
    }

    return 0;
}
//*/

//***********ZAD 3 
//a
/*int main(void) {
    printf("Poczatek\n");
    execl("/bin/ls", "ls", "-al", NULL); //roznica miedzy execl a execlp??
    printf("Koniec\n");
    return 0;
}*/
//b
/*
#define PATH "/home/cardaver/Work/V_semester/SCR/Procesy/src/podmianka"
int main(void) {
    printf("Poczatek\n");
    execl(PATH, "./podmianka", NULL);
    return 0;
}*/
//The first argument, by convention, should point to the filename associated with the file being executed
//*/

//ZAD 7

int main(void) {

    for(int i = 0; i < 10; ++i) {
        int res = fork();

        if(res == -1) {
            perror("Fork: ");
            printf("nr %d\n", res);
            exit(1);
        }

        if(res == 0) {
            printf("Dziecko\n");
            exit(0);
        }
        else {
            sleep(30);
            wait(NULL);
            exit(0);
        }
    }
    return 0;
}