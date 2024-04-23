#include <glob.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>
#include <sys/types.h>

void fun(int id);
void clear(void);

glob_t buf;
int idx, bf = -1;
char flag;
pid_t pid;

int main(int argc, char const *argv[]) {
	buf.gl_pathc = 0;
	buf.gl_pathv = NULL;

	glob("/home/wang/Music/*.mp3", 0, NULL, &buf);

	signal(17, fun);

	pid = fork();
	if (pid > 0) {
		while (1) {
			scanf("%c", &flag);
			switch (flag) {
				case '4': bf = -1;kill(pid, 9);break;
				case '6': bf = -1;kill(pid, 9);break;
				case '5': 
					bf = ~bf;
					if (bf) kill(pid, 18);
					else kill(pid, 19);
					break;
				case '0': 
					atexit(clear);
					signal(17, SIG_IGN);
					return 0;
			}
		}
	}
	if (pid == 0) {
		execlp("mpg123", "mpg123", buf.gl_pathv[idx], NULL);
	}
	return 0;
}

void clear(void) {
	kill(pid, 9);
	system("stty echo");
	printf("\033[?25h");
}

void fun(int id) {
	int a;
	pid_t n = waitpid(pid, &a, WNOHANG);
	if (n == pid) {
		if (WIFEXITED(a)) {
			idx = (idx+1 >= buf.gl_pathc ? 0 : idx+1);
		} else {
			if (flag == '4') {
				idx = (idx-1 <= -1 ? buf.gl_pathc-1 : idx-1);
			} else {
				idx = (idx+1 >= buf.gl_pathc ? 0 : idx+1);
			}
		}
		pid = fork();
		if (pid == 0) {
			execlp("mpg123", "mpg123", buf.gl_pathv[idx], NULL);
		}
	}
	
}