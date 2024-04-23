#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

int main() {
	// fork();
	// fork();
	// fork();

	printf("hello world");
	pid_t p = getpid();
	pid_t pp = getppid();
	printf("%d -> %d\n", pp, p);
	pid_t pid = fork();
	if (pid > 0) {
		pid_t a = wait(NULL);
		printf("我是父进程, a = %d\n", a);
	}
	if (pid == 0)
	{
		printf("我是子进程, pid = %d\n", pid);
		sleep(3);
	}
	exit(0);
	return 0;
}