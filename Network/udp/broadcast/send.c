#include <asm-generic/socket.h>
#include <netinet/in.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>

int main(int argc, char const *argv[]) {
	//创建套接字
	int sockfd = socket(AF_INET, SOCK_DGRAM, 0);
	//设置套接字为广播类型
	/*

	int sockfd > 
	int level > 选项所在级别 SOL_SOCKET(广播)
	int optname > SO_BROADCAST
	const void *optval > 
	socklen_t optlen > 
	*/
	int val = 1;
	int res = setsockopt(sockfd, SOL_SOCKET, \
		SO_BROADCAST, &val, sizeof(int));
	//发送
	char buf[110] = {0};
	struct sockaddr_in snd_addr;
	snd_addr.sin_family = AF_INET;
	snd_addr.sin_port = htons(12340);
	snd_addr.sin_addr.s_addr = inet_addr("192.168.43.255");
	while (1) {
		scanf("%s", buf);
		sendto(sockfd, buf, sizeof(buf), 0, \
		(struct sockaddr *)&snd_addr, sizeof(snd_addr));
	}
	
	return 0;
}