#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>

int main() {
	pid_t pid = vfork();
	if (pid > 0) {
		printf("-----父\n");
	}
	if (pid == 0) {
		printf("-----子\n");
		//
		execl("./system", "system", NULL);
		printf("=================\n");
		_exit(0);
	}
}
