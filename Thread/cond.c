#include <pthread.h>
#include <stdio.h>
#include <unistd.h>

void * fun1(void * a);
void * fun2(void * a);
void * fun3(void * a);

pthread_mutex_t lock = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t cond;

int val;

int main(int argc, char const *argv[]) {
	//初始化条件变量
	pthread_cond_init(&cond, NULL);

	pthread_t id1, id2, id3;

	pthread_create(&id1, NULL, fun1, NULL);
	pthread_create(&id2, NULL, fun2, NULL);
	pthread_create(&id3, NULL, fun3, NULL);

	pthread_join(id1, NULL);
	pthread_join(id2, NULL);
	pthread_join(id3, NULL);

	pthread_cond_destroy(&cond);

	pthread_exit(NULL);
	
	return 0;
}

void * fun1(void * a) {
	printf("等11\n");
	pthread_cond_wait(&cond, &lock);
	printf("上11\n");
	return 0;
}
void * fun2(void * a) {
	usleep(100);
	printf("等22\n");
	pthread_cond_wait(&cond, &lock);
	printf("上22\n");
	return 0;
}
void * fun3(void * a) {
	int f = 0;
	sleep(3);
	f = 1;
	if (f) {
		pthread_cond_signal(&cond);
	}
	return 0;
}
