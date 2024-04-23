#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <sys/types.h>
#include <unistd.h>

typedef struct {
	long mytype;
	char buf[110];
} MSG;

MSG snd, rcv;

void mysnd(int msqid) {
	scanf("%s", snd.buf);
	getchar();
	msgsnd(msqid, &snd, sizeof(snd) - sizeof(long), 0);
	if (!strcmp(snd.buf, "quit")) {
		exit(0);
	}
}

void myrcv(int msqid) {
	msgrcv(msqid, &rcv, sizeof(rcv) - sizeof(long), rcv.mytype, 0);
	if (!strcmp(rcv.buf, "quit")) {
		kill(getppid(), 9);
		exit(0);
	}
	printf("收到消息：%s\n", rcv.buf);
}

int main(int argc, char const *argv[]) {

	key_t keyw = ftok("/", 1);
	int msqidw = msgget(keyw, IPC_CREAT|0777);
	key_t keyr = ftok("/", 2);
	int msqidr = msgget(keyr, IPC_CREAT|0777);

	snd.mytype = 1;
	rcv.mytype = 2;

	pid_t pid = fork();
	
	if (pid > 0) {
		while (1) {
			mysnd(msqidw);
		}
	} else if (pid == 0) {
		while (1) {
			myrcv(msqidr);
		}
	}
	

	return 0;
}