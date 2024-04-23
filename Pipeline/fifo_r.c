#include <fcntl.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <stdio.h>
#include <unistd.h>

int main(int argc, char const *argv[]) {
	if (access("./1.fifo", F_OK)) {
		int res = mkfifo("./1.fifo", 0777);
		if (res) {
			perror("mkfifo");
		}
	}
	char buf[110] = {0};

	int fd = open("./1.fifo", O_RDONLY);

	while (1) {
		int len = read(fd, buf, 100);
		if (!len) return 0;
		printf("从管道读取:%s\n", buf);
		memset(buf, 0, sizeof(buf));
	}
	
	return 0;
}