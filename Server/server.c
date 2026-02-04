#include <stdio.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>

#define PORT 5001
#define SIZE 500

void init_addr(struct sockaddr_in *addr, int port) {
    addr->sin_family = AF_INET;
    addr->sin_port = htons(port);
    addr->sin_addr.s_addr = INADDR_ANY;
}

int main(void) {
    int shut_d, r, new_sd, l, sd, b;
    struct sockaddr_in addr, new_addr;
    char buf[SIZE];
    if((sd = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        perror("socket");
        return 1;
    }
    init_addr(&addr, PORT);
    if((b = bind(sd, (struct sockaddr*)&addr, sizeof(addr))) < 0) {
        perror("bind");
        return 1;
    }
    if((l = listen(sd, SIZE)) < 0) {
        perror("listen");
        return 1;
    }
    init_addr(&new_addr, PORT);
    socklen_t addr_len = sizeof(struct sockaddr_in);
    if((new_sd = accept(sd, (struct sockaddr*)&new_addr, &addr_len)) < 0) {
        perror("accept");
        return 1;
    }
    if((r = read(new_sd, buf, SIZE)) < 0) {
        perror("read");
        return 1;
    }
    printf("%s", buf);
    if((shut_d = shutdown(sd, SHUT_RDWR)) < 0) {
        perror("shutdown");
        return 1;
    }
    return 0;
}

