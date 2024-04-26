#include <netinet/in.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>

int main(int argc, char const *argv[]) {
	//创建套接字
	int sockfd = socket(AF_INET, SOCK_DGRAM, 0);
	//绑定
	struct sockaddr_in sock;
	sock.sin_family = AF_INET;
	sock.sin_port = htons(12340);
	sock.sin_addr.s_addr = INADDR_ANY;//本地地址
	int res = bind(sockfd, (struct sockaddr *)&sock, sizeof(sock));
	if (res == -1) {
		perror("bind");
	}
	
	char buf[110] = {0};
	struct sockaddr_in rcv_addr;
	unsigned int len = sizeof(rcv_addr);
	while (1) {
		recvfrom(sockfd, buf, sizeof(buf), 0, \
			(struct sockaddr *)&rcv_addr, &len);
		printf(">>>%s\n", buf);
	}
	
	return 0;
}