#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>

void error_handling(char *message);

int main(int argc, char* argv[])
{
	int sock;
	struct sockaddr_in serv_addr;
	char message[30];
	int str_len;
	
	if(argc!=3){
		printf("Usage : %s <IP> <port>\n", argv[0]);
		exit(1);
	}
	//初始化建立一个服务端的scoket
	sock=socket(PF_INET, SOCK_STREAM, 0);
	if(sock == -1)
		error_handling("socket() error");
	
	memset(&serv_addr, 0, sizeof(serv_addr));
	serv_addr.sin_family=AF_INET;
	serv_addr.sin_addr.s_addr=inet_addr(argv[1]);//传入的参数：服务端ip地址
	serv_addr.sin_port=htons(atoi(argv[2]));//传入的参数：服务端端口号

	//连接：通过服务端的ip和端口连接服务端
	if(connect(sock, (struct sockaddr*)&serv_addr, sizeof(serv_addr))==-1) 
		error_handling("connect() error!");

	//读取：通过建立好的socket读取到服务端发送过来的信息message
	str_len=read(sock, message, sizeof(message)-1);
	if(str_len==-1)
		error_handling("read() error!");

	//在显示屏上打印 message
	printf("Message from server: %s \n", message);  


	//给服务端发送应答消息
	char response_message[]="  I have recieved your message !!!";
	write(sock,response_message,sizeof(response_message));

	//关闭socket
	close(sock);

	return 0;
}

void error_handling(char *message)
{
	fputs(message, stderr);
	fputc('\n', stderr);
	exit(1);
}
