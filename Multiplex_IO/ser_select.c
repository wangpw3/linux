#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/select.h>

void * fun(void * a);

pthread_t id[10];
int clifd[10], maxfd, res;
char r_buf[110], w_buf[110];

int main(int argc, char const *argv[]) {
    memset(clifd, -1, sizeof(clifd));
    int sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd == -1) {
        perror("socker");
    }
	int val = 1;
	setsockopt(sockfd,SOL_SOCKET,SO_REUSEADDR,&val,sizeof(int));
    
    struct sockaddr_in ser_addr;
    ser_addr.sin_family = AF_INET;
    ser_addr.sin_port = htons(12340);//htons:把端口号转换为网络字节序
    ser_addr.sin_addr.s_addr = inet_addr("127.0.0.1");//inet_addr:把点分十进制转换为网络字节序
    int res = bind(sockfd, (struct sockaddr *)&ser_addr, sizeof(ser_addr));
    if (res == -1) {
        perror("bind");
    }
    
    res = listen(sockfd, 5);
    if (res == -1) {
        perror("listen");
    }

	
	//创建监听集合
	fd_set readset, bpset;
	//备份集合初始化
	FD_ZERO(&bpset);
	//将连接套接字的文件描述符存入备份集合
	FD_SET(sockfd, &bpset);

	/*
	int select >> 成功(发生异动的文件描述符的个数) / 失败(-1) / 超时(0)
	int nfds > 监听集合中最大的文件描述符+1
	fd_set *readfds > 监听集合首地址，监听读异动
	fd_set *writefds > 监听集合首地址，监听写异动
	fd_set *exceptfds > 监听集合首地址，监听异常异动
	struct timeval *timeout > 设置监听超时时间 / 死等NULL
	*/
	//select完成多路IO复用
	maxfd = sockfd;
	int cont = 0;
	struct sockaddr_in cli_addr;
    unsigned int len = sizeof(cli_addr);
	while (1) {
		readset = bpset;//由于监听集合每次要清空 所以要用备份给监听赋值
		res = select(maxfd+1, &readset, NULL, NULL, NULL);
		//连接套接字异动
		if (FD_ISSET(sockfd, &readset)) {
			clifd[cont] = accept(sockfd, (struct sockaddr *)&cli_addr, &len);
			printf(">>%d\n",cont);
			if (clifd[cont] > maxfd) {
				maxfd = clifd[cont];
			}
			FD_SET(clifd[cont], &bpset);
			cont ++;
		}
		//通信套接字异动
		for(int i = 0; i < cont; i++) {
			//判断哪个套接字异动
			if (FD_ISSET(clifd[i], &readset)) {
				int ren = recv(clifd[i], r_buf, sizeof(r_buf)-1, 0);
				
				if (ren == 0) {
					cont --;
					FD_CLR(clifd[i], &bpset);
					for(int j = i; j < cont; j++) {
						clifd[j] = clifd[j+1];
					}
				}
				if (ren > 0) {
					for (int j = 0; j < cont; j++) {
						if (j != i && clifd[j] != -1) {
							send(clifd[i], r_buf, len, 0);
						}
					}
				}
			}
		}
	}
    
	
    close(sockfd);
    return 0;
}