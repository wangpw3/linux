#include <signal.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <stdio.h>
#include <string.h>

int main(int argc, char const *argv[]) {

	int fd[2] = {0};
	pipe(fd);

	pid_t pid = fork();
	if (pid > 0) {
		char w_buf[110] = {0};
		close(fd[0]);
		while (1) {
			printf("向子进程发送:\n");
			scanf("%s", w_buf);
			if (!strcmp(w_buf, "quit"))
			{
				kill(pid, 9);
				exit(0);
			}
			write(fd[1], w_buf, strlen(w_buf));
			usleep(5000);
		}
		
	}
	if (pid == 0) {
		char r_buf[110] = {0};
		close(fd[1]);
		while (1) {
			int read_f = read(fd[0], r_buf, 100);
			if (read_f) {
				printf("从父进程接收:\n%s\n", r_buf);
				memset(r_buf, 0, sizeof(r_buf));
			}
		}
		
	}
	return 0;
}