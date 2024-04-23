#include <dirent.h>
#include <stdio.h>
#include <string.h>
#include <sys/stat.h>
#include <unistd.h>
char *(mu[110]);
int len = 0;
int main() {
	DIR * od = opendir(".");
	if (od == NULL) {
		perror("opendir");
		return -1;
	}
	struct dirent * rd = NULL;
	char p[4] = {'3','p','m','.'};
	while ((rd = readdir(od))) {
		if(rd->d_type == DT_REG) {
			int l = strlen(rd->d_name);
			for(int i = l-1; i>=l-4; i--) {
				if(rd->d_name[i] != p[l-i+-1]) goto NOO;
			}
			mu[len++] = rd->d_name;
			printf("%s\n", rd->d_name);
		}
NOO:;
	}
	printf("--------------------------\n");
	int id = 0;

	while(1) {
		char f = getchar();
		getchar();
		if(f == 's') {
			puts(mu[id = ((id-1)+len)%len]);
		}
		else if (f == 'x') {
			puts(mu[id = ((id+1)+len)%len]);
		}
		else return 0;
	}
	return 0;
}