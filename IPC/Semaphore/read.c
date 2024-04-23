#include <stdio.h>
#include <sys/ipc.h>
#include <sys/shm.h>


int main(int argc, char const *argv[]) {
	//创建键值
	key_t key = ftok("/", 222);
	//创建/打开共享内存
	int shmid = shmget(key, 4096, IPC_CREAT|0777);
	//映射
	char * str = (char *)shmat(shmid, NULL, 0);
	//读取并打印
	printf("%s\n", str);
	shmdt(str);
	shmctl(shmid, IPC_RMID, NULL);
	return 0;
}