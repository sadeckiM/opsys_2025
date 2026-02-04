#include "task.h"
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <mqueue.h>
#include <string.h>

void return_to_master(struct Task *t) {
    char name[64];
    get_mq_name(name, &t->pid);

    mqd_t mqd = mq_open(name, O_WRONLY);
    if(mqd == -1) {
        perror("mq_open slave to master");
        return;
    }
    if(mq_send(mqd, (const char*)t, sizeof(struct Task), 0) == -1) {
            perror("mq_send slave");
    }
    mq_close(mqd);
}
void slave(void) {
    mqd_t mqd = mq_open("/mqd", O_CREAT | O_RDONLY, 0666, NULL);

    if(mqd == -1) {
        perror("mq_open slave");
        exit(EXIT_FAILURE);
    }
    struct mq_attr attr;
    mq_getattr(mqd, &attr);

    struct Task *task;
    char *buf = (char *) malloc(attr.mq_msgsize);
    if(buf == NULL) {
        perror("malloc");
        exit(EXIT_FAILURE);
    }

    while(1) {
        ssize_t num_bytes = mq_receive(mqd, buf, attr.mq_msgsize, NULL);
        if(num_bytes == -1) {
            perror("mq_receive");
            continue;
        }

        task = (struct Task *)buf;
        return_to_master(task);
        sleep(1);
    }
    mq_close(mqd);
}

int main(int argc, char **argv) {
    slave();
    return 0;
}
