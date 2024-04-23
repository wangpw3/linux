#include <sys/types.h>
#include <sys/ipc.h>
#include <stdio.h>

int main(int argc, char const *argv[]) {
	key_t key = ftok("/", 21);
	printf("%d\n", key);
	return 0;
}