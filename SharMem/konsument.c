#include <fcntl.h>
#include <stdio.h>
#include <sys/mman.h>

#define SIZE 128

int main(void) {
    const char* name = "/lab_shm";
    char buf[SIZE];

    int fd = shm_open(name, O_RDWR, 0666);

    if(fd == -1) {perror("shm_open"); return 1; }

    void *ptr = mmap(0, SIZE, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);

    if(ptr == MAP_FAILED) {perror("mmap"); return 1; }

    printf("Odczytano: %s\n", (char*) ptr);
    shm_unlink(name);
    return 0;
}
