#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>

void error_handling(char *message);

int main(int argc, char *argv[])
{
	int serv_sock;
	int clnt_sock;

	struct sockaddr_in serv_addr;
	struct sockaddr_in clnt_addr;
	socklen_t clnt_addr_size;

	char message[]="Hello World!";
	
	if(argc!=2){
		printf("Usage : %s <port>\n", argv[0]);
		exit(1);
	}
	//初始化建立一个scoket
	serv_sock=socket(PF_INET, SOCK_STREAM, 0);
	if(serv_sock == -1)
		error_handling("socket() error");
	
	memset(&serv_addr, 0, sizeof(serv_addr));
	serv_addr.sin_family=AF_INET;
	serv_addr.sin_addr.s_addr=htonl(INADDR_ANY);
	serv_addr.sin_port=htons(atoi(argv[1]));//传入的参数：服务端使用的端口号
	//绑定, 用serv_addr绑定之后，就会返回生成分配的serv_sock
	if(bind(serv_sock, (struct sockaddr*) &serv_addr, sizeof(serv_addr))==-1 )
		error_handling("bind() error"); 
	//监听
	if(listen(serv_sock, 5)==-1)
		error_handling("listen() error");
	
	clnt_addr_size=sizeof(clnt_addr);  
	//接收客户端法来的信息:      serv_sock 和clnt_addr一起，  从而返回一个 客户端socket
	clnt_sock=accept(serv_sock, (struct sockaddr*)&clnt_addr,&clnt_addr_size);
	if(clnt_sock==-1)
		error_handling("accept() error");  

	//read client ip
	char ipstr[16];
	inet_ntop(AF_INET,&clnt_addr, ipstr, sizeof(ipstr));
	 int port = ntohs(clnt_addr.sin_port);
	printf("客户端信息：ip:port  %s : %d\n",ipstr,port);

	// 把 message 写到clnt_sock，相当于发送给客户端
	write(clnt_sock, message, sizeof(message));


	//读取：通过建立好的socket读取到客户端发送过来的信息client_message
	char client_message[30];
	int str_len=read(clnt_sock, client_message, sizeof(client_message)-1);
	if(str_len == -1 )
		error_handling("read() error!");
	else
	{
			printf(" recieved client message, it's :  %s \n",client_message);
	}
	//关闭客户端套接字
	close(clnt_sock);	
	//关闭服务端套接字
	close(serv_sock);
	return 0;
}

void error_handling(char *message)
{
	fputs(message, stderr);
	fputc('\n', stderr);
	exit(1);
}

