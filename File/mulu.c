#include <stdio.h>
#include <string.h>
#include <dirent.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>

char fun_type(char types);

int main(int argc, char * argv[]) {

	DIR * od = opendir("/home/wang/linux");

	if (od == NULL) {
		perror("opendir");
		return -1;
	}

	if (!strcmp(argv[1], "ls")) {
		struct dirent * rd = NULL;
		while ((rd = readdir(od))) {
			printf("%c %s\n", fun_type(rd->d_type), rd->d_name);
		}
		
	}
	else if(!strcmp(argv[1], "mkdir")) {
		int mk = mkdir(argv[argc - 1], 0777);
		if (mk == -1) {
			perror("mkdir");
			return -1;
		}
	}
	else if (!strcmp(argv[1], "rm")) {
		rmdir(argv[argc - 1]);
	}
	else {
		perror("error");
	}
	closedir(od);

	return 0;
}

char fun_type(char types) {
	char type;

	if(types == DT_BLK) type = 'b';
	if(types == DT_CHR) type = 'c';
	if(types == DT_DIR) type = 'd';
	if(types == DT_FIFO) type = 'p';
	if(types == DT_LNK) type = 'l';
	if(types == DT_REG) type = '-';
	if(types == DT_SOCK) type = 's';

	return type;
}