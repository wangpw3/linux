#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <sys/types.h>
#include <unistd.h>
#include <pthread.h>

void * fun(void * a);

int sockfd;

int main(int argc, char const *argv[]) {
	
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd == -1) {
        perror("socker");
    }
    struct sockaddr_in cli_addr;
    cli_addr.sin_family = AF_INET;
    cli_addr.sin_port = htons(12340);
    cli_addr.sin_addr.s_addr = inet_addr("127.0.0.1");
    int res = connect(sockfd, (struct sockaddr *) &cli_addr, sizeof(cli_addr));
    if (res == -1) {
        perror("connect");
    }
    char r_buf[110] = {0};
    int a = 0;
    pthread_t id = 0;
    pthread_create(&id, NULL, fun, (void *)&a);
    while (1) {
        scanf("%s", r_buf);
        getchar();
        send(sockfd, r_buf, strlen(r_buf), 0);
        if (!strcmp(r_buf, "quit")) {
            break;
        }
    }
    close(sockfd);
    return 0;
}

void * fun(void * a) {
    while (1) {
        char w_buf[110] = {0};
        int len = recv(sockfd, w_buf, 100, 0);
        if (!len) {
            exit(0);
        }
        printf(">>%s\n", w_buf);
        memset(w_buf, 0, sizeof(w_buf));
    }
    return 0;    
}