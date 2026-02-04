#include <stdio.h>
#include <mqueue.h>
#include <fcntl.h>
#include <stdlib.h>

//za pomoca setattr mozna zmienic tylko flage na O_NONBLOCK, reszta jest niezmienialna

int main(void) {
	struct mq_attr attr;
    struct mq_attr new_attr = {O_NONBLOCK, 5, 1024, 3};

	mq_unlink("/mqd");

	mqd_t mqd = mq_open("/mqd", O_CREAT | O_RDONLY, 0666, NULL);

	if(mqd == -1) {
		perror("mq_open");
		exit(EXIT_FAILURE);
	}
	
	if(mq_getattr(mqd, &attr) == -1) {
		perror("mq_getattr");
		exit(EXIT_FAILURE);
	}

	printf("Maksymalna liczba wiadomosci: %ld\n", attr.mq_maxmsg);
	printf("Maksymalny rozmiar wiadomosci: %ld\n", attr.mq_msgsize);
	printf("Flagi %d: %ld\n", attr.mq_flags);
	printf("Liczba wiadomosci w kolejce: %ld\n", attr.mq_curmsgs);

	printf("Po zmianie:\n");
	mq_setattr(mqd, &new_attr, NULL);
	printf("Maksymalna liczba wiadomosci: %ld\n", attr.mq_maxmsg);
	printf("Maksymalny rozmiar wiadomosci: %ld\n", attr.mq_msgsize);
	printf("Flagi %d: %ld\n",O_NONBLOCK, attr.mq_flags);
	printf("Liczba wiadomosci w kolejce: %ld\n", attr.mq_curmsgs);
	
	if(mq_close(mqd) == -1) {
		perror("mq_close");
		exit(EXIT_FAILURE);
	} //zamyka deskryptor
	
	if(mq_unlink("/mqd") == -1) {
		perror("mq_unlink");
		exit(EXIT_FAILURE);
	} //usuwa deskryptor

	return 0;
}
