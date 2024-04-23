#include <pthread.h>
#include <stdio.h>
#include <unistd.h>

void * fun(void * a);

int main(int argc, char const *argv[]) {
	int a = 10;
	pthread_t id = 0;
	//创建线程
	pthread_create(&id, NULL, fun, (void *)&a);
	printf("我是主线程, 副线程 id = %ld\n", id);
	//等到指定线程退出后解除阻塞
	//pthread_join(id, NULL);
	sleep(5);
	//取消线程
	pthread_cancel(id);
	//结束副线程
	pthread_exit(NULL);
	return 0;
}

void * fun(void * a) {
	int id = pthread_self();
	while (1) {
		sleep(1);
		printf("我是副线程, a = %d, id = %d\n", * (int *)a, id);
	}
	
	return 0;
}