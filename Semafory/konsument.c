#include "typedefs.h"

int main(void) {
    sem_t * SEM_EMPTY = sem_open("/sem_empty", O_CREAT, 0644, N); 
    sem_t * SEM_FULL = sem_open("/sem_full", O_CREAT, 0644, 0); 
    sem_t * SEM_MUTEX = sem_open("/sem_mutex", O_CREAT, 0644, 1); 
    
    if(SEM_EMPTY == SEM_FAILED || SEM_FULL == SEM_FAILED || SEM_MUTEX == SEM_FAILED) {
        perror("sem_open\n");
        return 1;
    }
 
    return 0;
}
