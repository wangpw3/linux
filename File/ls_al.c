#include <dirent.h>
#include <fcntl.h>
#include <stdio.h>
#include <sys/stat.h>
#include <time.h>
#include <unistd.h>

char fun_type(mode_t mode);
void fun_qx(mode_t mode);

struct stat buf = {0};

int main(int argc, char *argv[]) {
	DIR * od = opendir(".");
	if (od == 0) {
		perror("opendir");
		return -1;
	}
	struct dirent *rd = NULL;
	while ((rd = readdir(od))) {
		// 读取文件详细信息，并按照ls -l查出来的格式打印
		stat(rd->d_name, &buf);
		// 打印文件类型
		printf("%c", fun_type(buf.st_mode));
		// 打印文件权限
		fun_qx(buf.st_mode);
		// 打印文件的硬链接数
		printf("%3ld ", buf.st_nlink);
		// 打印文件大小
		printf("%6ld ", buf.st_size);
		// 打印时间
		struct tm *ftime = localtime(&buf.st_mtime);
		printf("%2d月	%2d %2d:%2d ", \
	ftime->tm_mon + 1, ftime->tm_mday, ftime->tm_hour, ftime->tm_min);
		// 打印文件名
		printf("%s\n", rd->d_name);
	}
}

char fun_type(mode_t mode) {
	char a = 0;
	switch (mode & S_IFMT) {
	case S_IFBLK:
		a = 'b';
		break;
	case S_IFCHR:
		a = 'c';
		break;
	case S_IFDIR:
		a = 'd';
		break;
	case S_IFIFO:
		a = 'p';
		break;
	case S_IFLNK:
		a = 'l';
		break;
	case S_IFREG:
		a = '-';
		break;
	case S_IFSOCK:
		a = 's';
		break;
	}
	return a;
}

void fun_qx(mode_t mode) {
	char buf[10] = {"---------"};
	if (mode & S_IRUSR)
		buf[0] = 'r';
	if (mode & S_IWUSR)
		buf[1] = 'w';
	if (mode & S_IXUSR)
		buf[2] = 'x';
	if (mode & S_IRGRP)
		buf[3] = 'r';
	if (mode & S_IWGRP)
		buf[4] = 'w';
	if (mode & S_IXGRP)
		buf[5] = 'x';
	if (mode & S_IROTH)
		buf[6] = 'r';
	if (mode & S_IWOTH)
		buf[7] = 'w';
	if (mode & S_IXOTH)
		buf[8] = 'x';
	printf("%s ", buf);
}