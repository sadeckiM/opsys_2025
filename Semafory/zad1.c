#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <string.h>
#include <semaphore.h>
#include <fcntl.h>

// Funkcja wypisująca napis znak po znaku - nasza SEKCJA KRYTYCZNA
void drukuj_powoli(const char *napis, sem_t * sem) {
    sem_wait(sem);
    for (int i = 0; napis[i] != '\0'; i++) {
        // Wypisanie jednego znaku
        putchar(napis[i]);

        // Wymuszenie opróżnienia bufora (żeby znak pojawił się od razu)
        fflush(stdout); 

        // Symulacja pracy / oddanie czasu procesora
        usleep(10000); // 10 milisekund opóźnienia
    }
    sem_post(sem);
}

int main(void) {
    // Rozwidlenie procesu
    pid_t pid = fork();
    sem_t * sem = sem_open("/sem1", O_CREAT, 0644, 1);

    if (pid == 0) {
        // --- Proces Potomny ---
        drukuj_powoli("Proces POTOMNY: To jest wazny komunikat.\n", sem);
        exit(0);
    } else if (pid > 0) {
        // --- Proces Macierzysty ---
        drukuj_powoli("Proces MACIERZYSTY: A to jest inny tekst.\n", sem);

        // Czekanie na zakończenie dziecka
        wait(NULL);
    } else {
        perror("Błąd fork");
        sem_close(sem);
        return 1;
    }
    sem_unlink("/sem1");
    return 0;
}
