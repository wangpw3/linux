#include <signal.h>
#include <stdio.h>
#include <unistd.h>

int main(int argc, char const *argv[])
{
	int n = 0;
	pid_t pid = fork();
	if (pid > 0) {
		printf("-------F\n");
	} else if (pid == 0) {
		while (1) {
			printf("-------Z\n");
			sleep(1);
			n++;
			if (n > 10) {
				//向自身发送 9 号信号
				raise(9);
			}
		}
	}
	return 0;
}