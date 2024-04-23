#include <pthread.h>
#include <stdio.h>
#include <unistd.h>

void * fun(void * a);
void fun1(void * a);

int main(int argc, char const *argv[]) {
	int a = 10;
	pthread_t id = 0;
	//创建线程
	pthread_create(&id, NULL, fun, (void *)&a);
	printf("我是主线程, 副线程 id = %ld\n", id);
	//等到指定线程退出后解除阻塞
	//pthread_join(id, NULL);
	sleep(2);
	pthread_cleanup_push(fun1, (void *)&id);
	sleep(1);
	pthread_cleanup_pop(1);
	sleep(2);
	//结束副线程
	printf("----------取消\n");
	pthread_exit(NULL);
	
	return 0;
}

void * fun(void * a) {
	int id = pthread_self();
	while (1) {
		printf("我是副线程, a = %d, id = %d\n", * (int *)a, id);
		sleep(1);
	}
	
	return 0;
}

void fun1(void * a) {
	pthread_t * id = (pthread_t *)a;
	//取消线程
	pthread_cancel(*id);
}