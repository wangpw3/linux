#include <stdio.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <stdlib.h>

int main(int argc, char const *argv[]) {

	key_t key = ftok("/", 1);
	int msqid = msgget(key, IPC_CREAT|0777);
	//printf("%d %d\n",key, msqid);
	msgctl(msqid, IPC_RMID, NULL);
	msgctl(atoi(argv[1]), IPC_RMID, NULL);
	return 0;
}