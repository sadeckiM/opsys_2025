#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>

int main(void) {

	const char* text = "Tekst dla soutfd.\n";
	int soutfd = dup(STDERR_FILENO);
	write(soutfd, text, strlen(text));

	FILE* fakeout = fdopen(soutfd, "w");

	if(fakeout == NULL) {
		perror("blad otwarcia pliku");
		exit(EXIT_FAILURE);
	}

	printf("Normalny printf\n");
	fprintf(stdout, "Tekst na stdout\n");
	fprintf(fakeout, "Tekst na fake stdout.\n");

	return 0;
}


