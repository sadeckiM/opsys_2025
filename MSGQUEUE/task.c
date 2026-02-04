#include "task.h"
#include <stdlib.h>
#include <stdio.h>

void attr_params(struct mq_attr * attr) {
    attr->mq_maxmsg = 10;
    attr->mq_curmsgs = 0;
    attr->mq_msgsize = sizeof(struct Task);
    attr->mq_flags = 0;
}

void get_mq_name(char* buf, pid_t *p) {
    int len = sprintf(buf, "/task_%d", *p);
    buf[len] = '\0';

    if(len < 1) {
        perror("get_mq_name");
        exit(EXIT_FAILURE);
    }
} 
