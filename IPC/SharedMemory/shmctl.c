#include <sys/ipc.h>
#include <sys/shm.h>
#include <stdlib.h>

int main(int argc, char const *argv[]) {
	//创建键值
	key_t key = ftok("/", 22);
	//创建打开共享内存
	int shmid = shmget(key, 1024, IPC_CREAT|0777);
	//删除
	shmctl(196671, IPC_RMID, NULL);
	return 0;
}