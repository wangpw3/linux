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

void * fun(void * a);

int clifd[10], sum;

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
    printf("用户人数:");
	scanf("%d", &sum);
	struct sockaddr_in cli_addr;
    unsigned int len = sizeof(cli_addr);
    pthread_t id[10] = {0};
	for (long i = 0; i < sum; i++)
	{
		clifd[i] = accept(sockfd, (struct sockaddr *)&cli_addr, &len);
		long num = i;
		printf("用户<%ld>登陆\n", i);
		pthread_create(&id[i], NULL, fun, (void *)num);
	}
	for (int i = 0; i < sum; i++) {
		pthread_join(id[i], NULL);
	}
	
    close(sockfd);
    return 0;
}

void * fun(void * a) {
	long idx = (long)a;
	char buf[110] = {0};
	while (1) {
		int len = recv(clifd[idx], buf, sizeof(buf)-1, 0);
		if (len == -1) {
            perror("recv"); // 打印接收数据时的错误信息
            break;
        } else if (len == 0) {
            printf("用户<%ld>的连接已经关闭\n", idx);
            break;
        }
		if (strcmp(buf, "quit") == 0) {
            printf("用户<%ld>请求退出\n", idx);
            break;
        }
		printf("%ld->%s<%d\n", idx, buf, len);
		for (int i = 0; i < sum; i++) {
			if (i != idx) {
				send(clifd[i], buf, len, 0);
			}
		}
		memset(buf, 0, sizeof(buf));
	}
	close(clifd[idx]);
    clifd[idx] = -1;
    return 0;
}