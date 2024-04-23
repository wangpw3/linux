#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>

char buf[110];

int main(int argc, char * argv[]) {
	int fp1 = open(argv[1], O_RDONLY | O_CREAT, 0666);
	if(fp1 == -1) {
		perror("fp1");
	}
	
	int fp2 = open(argv[2], O_TRUNC | O_CREAT | O_WRONLY, 0666);
	if (fp2 == -1) {
		perror("fp2");
	}

	while (read(fp1, buf, 1)) {
		write(fp2, buf, sizeof(buf));
	}
	
	close(fp1);
	close(fp2);
	
	return 0;
}