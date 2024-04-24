#include <pthread.h>
#include <stdio.h>
#include <unistd.h>

void * fun(void * a);

/*
动态创建：锁占用的空间位于堆区。手动开辟手动释放，所以锁不用了之后，需要调用锁的销毁函数，去手动释放空间。
静态创建：锁占用的是静态存储区的空间，占用的资源由系统统一回收，不需要手动区释放空间的。
*/

//动态创建：1、创建互斥锁
pthread_mutex_t lock;
//静态创建一个快速互斥锁
//pthread_mutex_t lock = PTHREAD_MUTEX_INITIALIZER;

int val;

int main(int argc, char const *argv[]) {
	//动态创建：2、初始化互斥锁
	pthread_mutex_init(&lock, NULL);

	
	//创建副线程
	pthread_t id1, id2, id3;
	pthread_create(&id1, NULL, fun, NULL);
	pthread_create(&id2, NULL, fun, NULL);
	pthread_create(&id3, NULL, fun, NULL);
	printf("我是主线程\n");
	pthread_join(id1, NULL);
	pthread_join(id2, NULL);
	pthread_join(id3, NULL);
	printf("%d\n", val);
	pthread_mutex_destroy(&lock);
	pthread_exit(NULL);
	
	return 0;
}

void * fun(void * a) {

	for (int i = 0; i < 50000; i++)
	{
		pthread_mutex_lock(&lock);
		val ++;
		pthread_mutex_unlock(&lock);
	}
	return 0;
}
