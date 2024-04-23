#include <fcntl.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <stdio.h>
#include <unistd.h>

int main(int argc, char const *argv[]) {
	int res = mkfifo("./1.fifo", 0777);
	if (res) {
		perror("mkfifo");
	}

	char buf[110] = {0};

	int fd = open("./1.fifo", O_WRONLY);
	while (1) {
		printf("向管道输入:");
		scanf("%s", buf);
		if(!strcmp(buf, "quit")) return 0;
		write(fd, buf, strlen(buf));
	}
	
	return 0;
}