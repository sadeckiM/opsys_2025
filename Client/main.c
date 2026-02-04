#include <sys/socket.h>
#include <stdio.h>
#include <netinet/in.h>
#include <string.h>

#define PORT 5001

int main(void) {
    int c, sd, s;
    const char* text = "Hello World\n";
    if((sd = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        perror("socket");
        return 1;
    }
    struct sockaddr_in addr;
    addr.sin_family = AF_INET;
    addr.sin_addr.s_addr = INADDR_ANY;
    addr.sin_port = htons(PORT);
    if((c = connect(sd, (struct sockaddr*)&addr, sizeof(addr))) < 0) {
        perror("connect");
        return 1;
    }
    if((s = send(sd, text, strlen(text), 0)) < 0) {
        perror("send");
        return 1;
    }
    return 0;
}
