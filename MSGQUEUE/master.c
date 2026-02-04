#include "task.h"
#include <stdio.h>
#include <stdlib.h>
#include <mqueue.h>
#include <time.h>
#include <unistd.h>
#include <fcntl.h>

mqd_t prepare_for_data(struct mq_attr * a, const char* name) {

    mqd_t mqd = mq_open(name, O_CREAT | O_RDONLY, 0666, a);
    
    if(mqd == -1) {
        perror("mq_open");
        printf("%s", name);
        exit(EXIT_FAILURE);
    }
    return mqd;
}

void receive_from_slave(mqd_t *mqd, struct mq_attr *a) {
    struct Task *task;
    char *buf = (char *) malloc(a->mq_msgsize);
    if(buf == NULL) {
        perror("malloc");
        exit(EXIT_FAILURE);
    }

    ssize_t num_bytes = mq_receive(*mqd, buf, a->mq_msgsize, NULL);
    if(num_bytes == -1) {
        perror("mq_receive");
        printf("%d", task->pid);
        exit(EXIT_FAILURE);
    }

    task = (struct Task *)buf;
    printf("Odebrano z %d: a=%d, b=%d, a+b=%d\n", task->pid, task->a, task->b, task->a+task->b);
    free(buf);
}

void master(unsigned int task_amount) {
    srand(time(NULL));
    pid_t pid = getpid();
    struct mq_attr attr;
    attr_params(&attr);
    char name[64] = {0};
    get_mq_name(name, &pid);
    mqd_t mqd_r = prepare_for_data(&attr, name);
    
    mqd_t mqd = mq_open("/mqd", O_CREAT | O_WRONLY, 0666, &attr);
    
    if(mqd == -1) {
        perror("mq_open master");
        exit(EXIT_FAILURE);
    }
    struct Task task;

    for(int i = 0; i < task_amount; ++i) {
        task.pid = pid;
        task.task_num = i;
        task.a = rand();
        task.b = rand();

        if(mq_send(mqd, (const char*)&task, sizeof(struct Task), 0) == -1) {
            perror("mq_send master");
            exit(EXIT_FAILURE);
        }
        receive_from_slave(&mqd_r, &attr);
    }
    if(mq_close(mqd) == -1) {
        perror("mq_close master");
        exit(EXIT_FAILURE);
    }

    if(mq_close(mqd_r) == -1) {
        perror("mq_close master_r");
        exit(EXIT_FAILURE);
    }

    mq_unlink(name);
}

int main(int argc, char **argv) {
    if (argc == 2) {
        master(atoi(argv[1]));
    }
    else {
        printf("Niepoprawna liczba argumentow.\n");
        printf("Wywolanie: ./producent n, n - liczba zadan.\n");
        exit(EXIT_FAILURE);
    }
    return 0;
}
