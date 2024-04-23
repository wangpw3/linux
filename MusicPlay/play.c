#include <glob.h>
#include <signal.h>
#include <stdio.h>
#include <sys/wait.h>
#include <unistd.h>
#include <sys/types.h>

void fun(int id);

glob_t buf;
int idx, flag;
pid_t pid;

int main(int argc, char const *argv[]) {
	buf.gl_pathc = 0;
	buf.gl_pathv = NULL;

	int gl_stat = glob("/home/wang/Music/*.mp3", 0, NULL, &buf);

	signal(17, fun);

	pid = vfork();
	if (pid > 0) {
		int status;
		while (1) {
			wait(&status);
			printf(">>>>>>1.下一首 0.上一首\n");
			scanf("%d", &flag);
			kill(pid, 17);
		}
	} else if (pid == 0) {
		execlp("mpg123", "mpg123", buf.gl_pathv[idx], NULL);
	}
	return 0;
}

void fun(int id) {
	if (flag == 1) {
		idx = (idx+1 == buf.gl_pathc ? 0 : idx+1);
	} else {
		idx = (idx-1 == -1 ? buf.gl_pathc : idx-1);
	}
	pid = fork();
	if (pid == 0) {
		execlp("mpg123", "mpg123", buf.gl_pathv[idx], NULL);
	}
}