#include "typedefs.h"
//  TODO: naprawić neotree ,
//  TODO: sharedmem, o co chodzi z warningiem w .h

void* map_memory(const int * size) {
    int fd = shm_open(name, O_CREAT | O_RDWR, 0666);
    if(fd == -1) { perror("shm_open"); return NULL; }

    if(ftruncate(fd, *size) == -1) {perror("ftruncate"); return NULL; }

    void *ptr = mmap(0, *size, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);
    if(ptr == MAP_FAILED) { perror("mmap"); return NULL; }

    ptr_read = ptr;
    ptr_write = ptr;

    return ptr;
}

int * ptr_read = NULL;
int * ptr_write = NULL;
const char* name = "/sh1";

int main(void) {
    sem_t * SEM_EMPTY = sem_open("/sem_empty", O_CREAT, 0666, N); 
    sem_t * SEM_FULL = sem_open("/sem_full", O_CREAT, 0666, 0); 
    sem_t * SEM_MUTEX = sem_open("/sem_mutex", O_CREAT, 0666, 1); 
    
    if(SEM_EMPTY == SEM_FAILED || SEM_FULL == SEM_FAILED || SEM_MUTEX == SEM_FAILED) {
        perror("sem_open\n");
        return 1;
    }
    void* mem = map_memory(&N);
    if(mem == NULL)
        return 1;
    sem_wait(SEM_EMPTY);
    sem_wait(SEM_MUTEX);
        sprintf((char*) mem, "wiadomosc\n");
        ptr_write += N;
    sem_post(SEM_FULL);
    sem_post(SEM_MUTEX);
    munmap(mem, N);

    return 0;
}
