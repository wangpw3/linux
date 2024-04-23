#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <signal.h>

int main() {
	pid_t pid = fork();
	if (pid > 0) {
		//kill(进程, 信号)
		printf("------父\n");
		sleep(5);
		kill(pid, 19);
		sleep(3);
		kill(pid, 18);
		sleep(1);
		kill(pid, 9);
	}
	if (pid == 0) {
		printf("------子\n");
		while (1) {
			printf("haha\n");
			sleep(1);
		}
	}
}
