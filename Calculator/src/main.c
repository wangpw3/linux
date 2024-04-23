#include <string.h>
#include <stdlib.h>

#include "jia.h"
#include "jian.h"
#include "cheng.h"
#include "chu.h"

int main(int argc, char * argv[]) {
	int a = atoi(argv[1]);
	int b = atoi(argv[3]);
	switch(*argv[2]) {
		case '+': jia(a, b); break;
		case '-': jian(a, b); break;
		case 'x': cheng(a, b); break;
		case '/': chu(a, b); break;
		default: break;
	}
	return 0;
}
