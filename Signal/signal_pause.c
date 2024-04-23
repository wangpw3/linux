#include <signal.h>
#include <unistd.h>
#include <stdio.h>

void fun(int id);

int main(int argc, char const *argv[]) {
	int n = 0;
	// 信号改写 
	// 9/19 不能改写
	signal(2, fun);
	while (1) {
		sleep(1);
		printf("%d\n", n++);
		if (n == 3) {
			//阻塞  直到接收到信号
			pause();
		}
	}
	return 0;
}

void fun(int id) {
	printf(">>>>>>>>>>>%d\n", id);
	return;
}