#include <sys/select.h>
#include <sys/types.h>
#include <unistd.h>




int main(int argc, char const *argv[]) {
	/* 创建监听集合
	int select >> 成功(发生异动的文件描述符的个数) / 失败(-1) / 超时(0)
	int nfds > 监听集合中最大的文件描述符
	fd_set *readfds > 监听集合首地址，监听读异动
	fd_set *writefds > 监听集合首地址，监听写异动
	fd_set *exceptfds > 监听集合首地址，监听异常异动
	struct timeval *timeout > 设置监听超时时间 / 死等NULL
	*/

	/* 把文件描述符从监听集合中删除
	void FD_CLR >> 
	int fd > 要删除的文件描述符
	fd_set *set > 监听集合的首地址
	*/
	
	/* 判断文件描述符是否在监听集合内
	int  FD_ISSET >> 在(真) / 不在(假)
	int fd > 要判断的文件描述符
	fd_set *set > 监听集合的首地址
	*/
	
	/* 往监听集合内添加文件描述符
	void FD_SET >> 
	int fd > 要添加的文件描述符
	fd_set *set > 监听集合的首地址
	*/
	
	/* 清空监听集合
	void FD_ZERO >> 
	fd_set *set > 监听集合的首地址
	*/
	return 0;
}