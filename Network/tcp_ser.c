#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <sys/types.h>
#include <unistd.h>

// struct in_addr
// {
// 	 in_addr_t   s_addr; /* 32 位 IPv4 地址，网络字节序 */
// };

// struct sockaddr_in {
//  	short int sin_family; 			/*地址族*/
//  	unsigned short int sin_port
// 		return -1;; 	/*端口号*/
//  	struct in_addr sin_addr; 		/*IP 地址*/
//  	unsigned char sin_zero[8]; 		/*未使用*/
// };

void * fun(void * a);

int clifd;

int main(int argc, char const *argv[]) {
	/*
	返回 >> 套接字的文件描述符/失败-1
	int domain > 协议族 AF_INET(IPV4)/AF_INET6(IPV6)
	int type > 通信协议 SOCK_STREAM(TCP)/SOCK_DGRAM(UDP)
	int protocol > 0
	*/
	int sockfd = socket(AF_INET, SOCK_STREAM, 0);
	if (sockfd == -1) {
		perror("socker");
	}
	/*
	绑定服务器 IP 和 端口 >> 成功0/失败-1
	int sockfd > 套接字的文件描述符
	const struct sockaddr_in ser_addr > 协议族 端口号 IP
	socklen_t addrlen > 结构体大小 sizeof
	*/
	struct sockaddr_in ser_addr;
	ser_addr.sin_family = AF_INET;
	ser_addr.sin_port = htons(12349);//htons:把端口号转换为网络字节序
	ser_addr.sin_addr.s_addr = inet_addr("192.168.43.74");//inet_addr:把点分十进制转换为网络字节序
	int res = bind(sockfd, (struct sockaddr *)&ser_addr, sizeof(ser_addr));
	if (res == -1) {
		perror("bind");
	}
	/*
	设置服务器同一时刻允许多少客户端连接 >> 成功0/失败-1
	int sockfd > 套接字的文件描述符
	int backlog > 最大监听数量
	*/
	res = listen(sockfd, 3);
	if (res == -1) {
		perror("bind");
	}
	/*
	阻塞
	等待客户端连接 >> 成功创建用于和该客户端的通信套接字且返回/失败-1
	int sockfd
	struct sockaddr_in *addr
	socklen_t *addrlen > 结构大小的地址
	*/
	struct sockaddr_in cli_addr;
	unsigned int len = sizeof(cli_addr);
	clifd = accept(sockfd, (struct sockaddr *)&cli_addr, &len);
	if (clifd == -1) {
		perror("accept");
	}
	/*
	收发数据 -- 
	send ssize_t >> 成功真正发送的数据大小 / 失败-1
		int sockfd > 通信套接字的文件描述符 (accept)
		const void *buf > 发送内容首地址
		size_t len > 发送长度
		int flags > 0阻塞
	recv ssize_t >> 成功真正接收的数据大小 / 失败-1
		int sockfd > 通信套接字的文件描述符 (accept)
		void *buf > 收到内容首地址
		size_t len > 收到长度
		int flags > 0阻塞
	*/
	char r_buf[110] = {0};
	int a = 0;
	pthread_t id = 0;
	pthread_create(&id, NULL, fun, (void *)&a);
	while (1) {
		scanf("%s", r_buf);
		getchar();
		send(clifd, r_buf, strlen(r_buf), 0);
		if (!strcmp(r_buf, "quit")) {
			break;
		}
	}
	
	close(sockfd);
	return 0;
}

void * fun(void * a) {
	char w_buf[110] = {0};
	while (1) {
		int len = recv(clifd, w_buf, 100, 0);
		if (!len) {
			exit(0);
		}
		printf(">>%s\n", w_buf);
		memset(w_buf, 0, sizeof(w_buf));
	}
	return 0;
}