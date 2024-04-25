#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>

int main(int argc, char const *argv[]) {
	//int domain > 协议族 AF_INET(IPV4)/AF_INET6(IPV6)
	//int type > 通信协议 SOCK_STREAM(TCP)/SOCK_DGRAM(UDP)
	//int protocol > 0
	int sockfd = socket(AF_INET, SOCK_STREAM, 0);
	if (sockfd == -1) {
		perror("socker");
		return -1;
	}
	// int bind(int sockfd, const struct sockaddr *addr, socklen_t addrlen);
	// int listen(int sockfd, int backlog);
	// int accept(int sockfd, struct sockaddr *addr, socklen_t *addrlen);
	// int connect(int sockfd, const struct sockaddr *addr, socklen_t addrlen);
	return 0;
}