#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/socket.h>

int main(void)
{	
	int fd1, fd2, fd3;
	fd1=socket(PF_INET, SOCK_STREAM, 0);
	//O_CREAT：必要时创建文件；O_WRONLY：只写打开；O_TRUNC：删除文件现有全部数据
	fd2=open("test.dat", O_CREAT|O_WRONLY|O_TRUNC);
	fd3=socket(PF_INET, SOCK_DGRAM, 0);
	
	printf("file descriptor 1: %d\n", fd1);
	printf("file descriptor 2: %d\n", fd2);
	printf("file descriptor 3: %d\n", fd3);
	
	close(fd1);
	close(fd2);
	close(fd3);
	return 0;
}