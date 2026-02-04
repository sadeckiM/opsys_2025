#include <unistd.h>
#include <mqueue.h>

struct Task {
	pid_t pid;
	unsigned int task_num;
	int a;
	int b;
};


void attr_params(struct mq_attr * attr);
void get_mq_name(char* buf, pid_t *p); 
