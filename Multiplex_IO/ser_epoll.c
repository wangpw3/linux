#include <stdio.h>
#include <string.h>
#include <sys/epoll.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <sys/types.h>
#include <unistd.h>

void * fun(void * a);

pthread_t id[10];
int clifd[10], maxfd, res;
char buf[110], w_buf[110];

int main(int argc, char const *argv[]) {
    int sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd == -1) {
        perror("socker");
    }
	maxfd = sockfd;
    
    struct sockaddr_in ser_addr;
    ser_addr.sin_family = AF_INET;
    ser_addr.sin_port = htons(12345);//htons:把端口号转换为网络字节序
    ser_addr.sin_addr.s_addr = inet_addr("127.0.0.1");//inet_addr:把点分十进制转换为网络字节序
    int res = bind(sockfd, (struct sockaddr *)&ser_addr, sizeof(ser_addr));
    if (res == -1) {
        perror("bind");
    }
    
    res = listen(sockfd, 5);
    if (res == -1) {
        perror("listen");
    }

	//创建句柄
    int epfd = epoll_create(1);
    //将连接套接字的文件描述符存入句柄
    struct epoll_event ev;
    ev.events = EPOLLIN;//可读异动
    ev.data.fd = sockfd;
    epoll_ctl(epfd,EPOLL_CTL_ADD,sockfd, &ev);
	int cont = 0;
	struct sockaddr_in cli_addr;
    unsigned int len = sizeof(cli_addr);
	//epoll完成多路io复用
	struct epoll_event evbuf[6] = {0};
	while (1) {
		int ren = epoll_wait(epfd, evbuf, 6, -1);
		for(int i = 0; i < ren; i++) {
			if(evbuf[i].data.fd == sockfd && (evbuf[i].events&&EPOLLIN)) {
				clifd[cont] = accept(sockfd, (struct sockaddr *)&cli_addr, &len);
				printf("用户<%d>登陆\n",clifd[cont]);
				ev.data.fd = clifd[cont];
				ev.events = EPOLLIN;
				epoll_ctl(epfd, EPOLL_CTL_ADD, clifd[cont], &ev);
				cont ++;
			} else if (evbuf[i].data.fd != sockfd && (evbuf[i].events&&EPOLLIN)) {
				int ren = recv(evbuf[i].data.fd, buf, 100, 0);
				if (ren == 0 || !strcmp(buf, "quit")) {
					printf("用户<%d>已下线!!\n", evbuf[i].data.fd);
					epoll_ctl(epfd, EPOLL_CTL_DEL, evbuf[i].data.fd, NULL);
					for(int k = 0; k < cont; k++) {
						if(clifd[k] == evbuf[i].data.fd) {
							for(int j = k; j < cont - 1; j++) {
								clifd[j] = clifd[j+1];
							}
							cont --;
							break;
						}
					}
				}
				if (ren > 0) {
					char str[125];
					sprintf(str,"%d : ", evbuf[i].data.fd);
					strcat(str, buf);
					for (int j = 0; j < cont; j++) {
						if (clifd[j] != evbuf[i].data.fd) {
							send(clifd[j], str, len, 0);
						}
					}
					memset(buf, 0, sizeof(buf));
				}
			}
		}
		
	}
    return 0;
}