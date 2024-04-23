#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>

int main() {
	//创建进程
	//先执行子进程
	pid_t pid = vfork();
	if (pid > 0) {
		printf("父\n");
	}
	if (pid == 0) {
		printf("子\n");
		_exit(0);
	}
}
