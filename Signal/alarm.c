#include <unistd.h>
#include <stdio.h>

int main(int argc, char const *argv[])
{
	pid_t pid = fork();
	if (pid > 0) {
		printf("-------F\n");
	} else if (pid == 0) {
		alarm(10);
		sleep(5);
		//闹钟，最后一个为准
		alarm(10);
		while (1) {
			sleep(1);
			printf("-------Z\n");
		}
	}
	return 0;
}