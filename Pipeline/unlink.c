#include <unistd.h>

int main(int argc, char const *argv[]) {
	unlink(argv[1]);
	return 0;
}