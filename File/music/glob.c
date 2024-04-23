#include <glob.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>

int main(int argc, char const *argv[])
{
	glob_t gl_struct;
	int gl_stat;

	gl_struct.gl_pathc = 0;
	gl_struct.gl_pathv = NULL;

	gl_stat = glob("/home/wang/Music/*.mp3", 0, NULL, &gl_struct);

	execlp("mpg123","mpg123" , gl_struct.gl_pathv[0], NULL);

	if (gl_stat == 0) {
		for (int i = 0; i < gl_struct.gl_pathc; i++) {
			printf("%s\n", gl_struct.gl_pathv[i]);
		}
	} else {
		perror("glob");
	}
	globfree(&gl_struct);
	return 0;
}