#include <netinet/in.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>

int main(int argc, char const *argv[]) {
	/*
	返回 >> 套接字的文件描述符/失败-1
	int domain > 协议族 AF_INET(IPV4)/AF_INET6(IPV6)
	int type > 通信协议 SOCK_STREAM(TCP)/SOCK_DGRAM(UDP)
	int protocol > 0
	*/
	int sockfd = socket(AF_INET, SOCK_DGRAM, 0);
	if (sockfd == -1) {
		perror("socker");
	}
	/*
	收发数据 -- 
	sendto ssize_t >> 成功真正发送的数据大小 / 失败-1
		int sockfd > 通信套接字的文件描述符 (accept)
		const void *buf > 发送内容首地址
		size_t len > 发送长度
		int flags > 0阻塞
		sockaddr_in *dest_addr > 接收方 IP 端口号
		socklen_t addrlen > 结构体大小
	recvfrom ssize_t >> 成功真正接收的数据大小 / 失败-1
		int sockfd > 通信套接字的文件描述符 (accept)
		void *buf > 收到内容首地址
		size_t len > 收到长度
		int flags > 0阻塞
		sockaddr_in *dest_addr > 发送方 IP 端口号
		socklen_t * addrlen > 结构体大小"首地址"
	*/
	char w_str[110] = {0}, r_str[110] = {0};
	struct sockaddr_in snd_addr, rcv_addr;
	unsigned int len = sizeof(struct sockaddr_in);
	snd_addr.sin_family = AF_INET;
	snd_addr.sin_port = htons(12345);
	snd_addr.sin_addr.s_addr = inet_addr("127.0.0.1");
	int a = 0;
	while (1) {
		scanf("%s", w_str);
		sendto(sockfd, w_str, sizeof(w_str), 0, \
		(struct sockaddr *)&snd_addr, len);
	}
	//recvfrom(sockfd, r_str, sizeof(r_str), 0, \
		(struct sockaddr *)&rcv_addr, &len);
	return 0;
}