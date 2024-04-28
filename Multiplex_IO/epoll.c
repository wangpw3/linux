#include <sys/epoll.h>

/*
struct epoll_event *event：
struct epoll_event {
	uint32_t events;  选择监听类型 
	epoll_data_t data;  文件描述符 
};
uint32_t events：
	EPOLLIN：可读性异动
	EPOLLOUT：可写异动
	EPOLLERR：异常异动
	
epoll_data_t data：
typedef union epoll_data {
	void *ptr;
	int fd;
	uint32_t u32;
	uint64_t u64;
} epoll_data_t;
*/

int main(int argc, char const *argv[]) {
	/*
	int epoll_wait >> 成功(发生异动的文件描述符的个数)/失败(-1)/超时(0)
	int epfd > 
	struct epoll_event *events > 	指向用来保存发生异动的套接字的信息的空间的首地址
									需要用户自己去定一个结构体数组，然后将该数组的首地址传入即可。
	int maxevents > 检测的最大个数。服务器中的 listen 设置的最大监听数量是 n，这个参数就填 n+1
	int timeout > 	超时时间
					=0，非阻塞
					>0，指定时间内阻塞
					-1，阻塞（死等）
	*/
	return 0;
}