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

int clifd[5], sum;

int main(int argc, char const *argv[]) {
    
    int sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd == -1) {
        perror("socker");
    }
	int val = 1;
	setsockopt(sockfd,SOL_SOCKET,SO_REUSEADDR,&val,sizeof(int));
    
    struct sockaddr_in ser_addr;
    ser_addr.sin_family = AF_INET;
    ser_addr.sin_port = htons(12349);//htons:把端口号转换为网络字节序
    ser_addr.sin_addr.s_addr = inet_addr("127.0.0.1");//inet_addr:把点分十进制转换为网络字节序
    int res = bind(sockfd, (struct sockaddr *)&ser_addr, sizeof(ser_addr));
    if (res == -1) {
        perror("bind");
    }
    
    res = listen(sockfd, 3);
    if (res == -1) {
        perror("listen");
    }
    printf("用户人数:");
	scanf("%d", &sum);
	struct sockaddr_in cli_addr;
    unsigned int len = sizeof(cli_addr);
    pthread_t id[5] = {0};
	for (int i = 0; i < sum; i++)
	{
		clifd[i] = accept(sockfd, (struct sockaddr *)&cli_addr, &len);
		pthread_create(&id[i], NULL, fun, (void *)&i);
	}
	for (int i = 0; i < sum; i++) {
		pthread_join(id[i], NULL);
	}
	
    close(sockfd);
    return 0;
}

void * fun(void * a) {
	int idx = *(int *)a;
	char buf[110] = {0};
	while (1) {
		int len = recv(clifd[idx], buf, strlen(buf), 0);
		printf("%d->%s<\n", idx, buf);
		for (int i = 0; i < sum; i++) {
			if (i != idx) {
				send(clifd[i], buf, strlen(buf), 0);
			}
		}
		memset(buf, 0, sizeof(buf));
	}
    return 0;
}