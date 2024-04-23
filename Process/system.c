#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>

int main() {
	pid_t pid = vfork();
	if (pid > 0) {
		printf("-----父\n");
	}
	if (pid == 0) {
		printf("-----子\n");
		//执行系统命令
		system("ls");
		printf("=================\n");
		_exit(0);
	}
}
