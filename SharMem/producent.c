#include <sys/mman.h>
#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>

#define SIZE 128

int main(void) {
    const char* name = "/lab_shm";
    char text[SIZE];
    int fd = shm_open(name, O_CREAT | O_RDWR, 0666);
    
    if(fd == -1) {perror("shm_open"); return 1; }
    
    if(ftruncate(fd, SIZE) == -1) {perror("ftruncate"); return 1; }

    void *mem = mmap(0, SIZE, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);
    
    if(mem == MAP_FAILED) {perror("mmap"); return 1; }
    
    printf("Podaj tekst do wczytania: \n");
    if(fgets(text, sizeof(text), stdin) != NULL) {
        size_t len = strlen(text);
        if(len > 0 && text[len - 1] == '\n')
            text[len - 1] = '\0';
        printf("Wczytano %s\n", text);
        sprintf((char*)mem, "%s", text);
        printf("Nacisnij cos, aby wyjsc.\n");
        getchar();
        getchar();
        return 0;
    } else {
        printf("Nie udalo sie wczytac tekstu.\n");
        return 1;
    }
}
