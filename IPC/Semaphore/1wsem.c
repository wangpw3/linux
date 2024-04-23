#include <string.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/sem.h>

#include <stdio.h>
#include <sys/shm.h>
#include <unistd.h>

key_t key;

union semun {
	int              val;    /* Value for SETVAL */
	struct semid_ds *buf;    /* Buffer for IPC_STAT, IPC_SET */
	unsigned short  *array;  /* Array for GETALL, SETALL */
	struct seminfo  *__buf;  /* Buffer for IPC_INFO
								(Linux-specific) */
};

struct sembuf sem;

void P(int semid) {
	sem.sem_flg = 0;
	sem.sem_num = 0;
	sem.sem_op = -1;
	semop(semid, &sem, 1);
}

void V(int semid) {
	sem.sem_flg = 0;
	sem.sem_num = 0;
	sem.sem_op = 1;
	semop(semid, &sem, 1);
}

int main(int argc, char const *argv[]) {
	//创建键值
	key = ftok("/", 111);
	//创建信号量集合 返回信号量集的标识符
	int semid = semget(key, 1, IPC_CREAT|0777);
	//初始化信号量集合中的0号信号量
	union semun s;
	s.val = 1;
	semctl(semid, 0, SETVAL, s);
	//获取当前信号量的值
	printf("%d\n", semctl(semid, 0, GETVAL));
	

	//创建键值
	key = ftok("/", 222);
	//创建/打开共享内存
	int shmid = shmget(key, 4096, IPC_CREAT|0777);
	//映射
	char * str = (char *)shmat(shmid, NULL, 0);

	int cont = 50;
	char * buff = "*";
	while (cont --) {
		P(semid);
		strcat(str, buff);
		usleep(1000);
		strcat(str, buff);
		V(semid);
	}

	//解除映射
	shmdt(str);
	//删除信号量集合
	//int val = semctl(semid, 0, IPC_RMID, GETVAL);//信号量当前的值 GETVAL
	return 0;
}