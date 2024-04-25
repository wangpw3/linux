#include <pthread.h>
#include <stdio.h>
#include <unistd.h>
#include <semaphore.h>

void * fun(void * a);

pthread_mutex_t lock = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t cond;

sem_t sem;

int val;

int main(int argc, char const *argv[]) {

	sem_init(&sem, 0, 1);

	pthread_t id1, id2, id3;

	pthread_create(&id1, NULL, fun, NULL);
	pthread_create(&id2, NULL, fun, NULL);
	pthread_create(&id3, NULL, fun, NULL);

	pthread_join(id1, NULL);
	pthread_join(id2, NULL);
	pthread_join(id3, NULL);

	int pp = 0;
	sem_getvalue(&sem, &pp);
	printf("pp = %d\n", pp);

	printf("val = %d\n", val);

	sem_destroy(&sem);

	pthread_exit(NULL);
	
	return 0;
}

void * fun(void * a) {
	for (int i = 0; i < 50000; i++)
	{
		sem_wait(&sem);
		val ++;
		sem_post(&sem);
	}
	return 0;
}
