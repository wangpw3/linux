#include <stdio.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <unistd.h>

int main(int argc, char const *argv[])
{
	pid_t pid = fork();
	if (pid == 0) {
		printf("-----子\n");
		sleep(2);
	} else if (pid > 0) {
		printf("-----父\n");
		int status;
		//阻塞等待子进程结束
		//接收子进程结束信号
		wait(&status);
		if (WIFEXITED(status)) {
			printf("status = %d\n", status);
		} else if (WIFSIGNALED(status)) {
			printf("xxxxxstatus = %d\n", status);
		}
		
	} else {
		perror("pid");
	}
	return 0;
}