#include <pthread.h>
#include <stdio.h>
#include <unistd.h>
#include <signal.h>


void * fun(void * a);
void fun1(void * a);

int main(int argc, char const *argv[]) {
	int a = 10;
	pthread_t id = 0;
	pthread_create(&id, NULL, fun, (void *)&a);
	printf("我是主线程, 副线程 id = %ld\n", id);
	sleep(5);
	pthread_kill(id, 9);
	pthread_exit(NULL);
	
	return 0;
}

void * fun(void * a) {
	long id = pthread_self();
	while (1) {
		printf("我是副线程, a = %d, id = %ld\n", * (int *)a, id);
		sleep(1);
	}
	
	return 0;
}

void fun1(void * a) {
	pthread_t * id = (pthread_t *)a;
	//取消线程
	pthread_cancel(*id);
}