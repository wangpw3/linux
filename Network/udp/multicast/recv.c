#include <arpa/inet.h>
#include <netinet/in.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <net/if.h>
/*
struct ip_mreqn
{
	struct in_addr imr_multiaddr; //组播地址 224.0.0.0 ~ 239.255.255.255
	struct in_addr imr_address; //本地地址 INADDR_ANY
	int imr_ifindex; //物理地址 > if_nametoifindex("ens33") -> 获取硬件ID的函数
};
*/
int main(int argc, char const *argv[]) {

	//创建套接字
	int sockfd = socket(AF_INET, SOCK_DGRAM, 0);
	if (sockfd == -1) {
		perror("socket");
	}
	/*
	int setsockopt >> 
	int sockfd
	int level > 层级: SOL_SOCKET (广播) / IPPROTO_IP (组播)
	int optname > 模式 创建组播(发送)：IP_MULTICAST_IF / 加入组播(接收)：IP_ADD_MEMBERSHIP
	const void *optval > struct ip_merqn
	socklen_t optlen > sizeof(struct ip_mreqn)
	*/
	struct ip_mreqn im;
	im.imr_address.s_addr = INADDR_ANY;
	im.imr_ifindex = if_nametoindex("ens33");
	im.imr_multiaddr.s_addr = inet_addr("224.1.1.1");
	int res = setsockopt(sockfd, IPPROTO_IP, \
		IP_ADD_MEMBERSHIP, &im, sizeof(im));
	if (res == -1) {
		perror("setsockopt");
	}

	//绑定
	struct sockaddr_in rcv_addr;
	unsigned int len = sizeof(rcv_addr);
	rcv_addr.sin_family = AF_INET;
	rcv_addr.sin_port = htons(12345);
	rcv_addr.sin_addr.s_addr = INADDR_ANY;
	res = bind(sockfd, (struct sockaddr *)&rcv_addr, len);
	if (res == -1) {
		perror("bind");
	}

	char buf[110] = {0};
	res = recvfrom(sockfd, buf, sizeof(buf), 0, \
		(struct sockaddr *)&rcv_addr, &len);
	if (res == -1) {
		perror("recvfrom");
	}
	printf(">>>%s\n", buf);
	return 0;
}