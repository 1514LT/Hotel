#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/ioctl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include "rfid_lib.h"
#include <sys/socket.h> //socket
#include <unistd.h>		//close
#include <string.h>		//memset strlen
#include <netinet/in.h> //struct sockaddr_in
#include <arpa/inet.h>	//inet_pton
//串口号
#if 0
#define UART_DEV "/dev/ttyUSB0"
#else
#define UART_DEV "/dev/ttySAC2"
#endif
int sockfd = 0;
int send_flag = 0;
void *recv_udp_func(void *arg);
int main(void)
{
	int len, i;
	char type;
	unsigned char id[18] = {0};
	//建立TCP客户端
	// 1、创建TCP套接字
	sockfd = socket(AF_INET, SOCK_STREAM, 0);
	if (sockfd < 0)
	{
		perror("socket");
		return 0;
	}

	// 2、连接服务器
	struct sockaddr_in server_addr;
	bzero(&server_addr, sizeof(server_addr));
	server_addr.sin_family = AF_INET;
	server_addr.sin_port = htons(8000);
	server_addr.sin_addr.s_addr = inet_addr("47.109.62.159");
	int ret = connect(sockfd, (struct sockaddr *)&server_addr, sizeof(server_addr));
	if (ret != 0)
	{
		perror("connect");
		return 0;
	}

	// 3、发送上线信息
	send(sockfd, "1:1", 3, 0);

#if 1
	pthread_t recv_tid;
	pthread_create(&recv_tid, NULL, recv_udp_func, NULL);

	//捕获信号
	uart_rfid_init(UART_DEV);
	while (1)
	{
		if (len = get_rfid_card_id(id, &type))
		{
			char card[128] = "";
			printf("%c类卡卡号:", type);
			for (i = 0; i < len; i++)
				sprintf(card + i * 2, "%02x", id[i]);
			printf("card=%s\n", card);

			if (send_flag == 1) //有cgi获取card
			{
				char data[128] = "";
				int data_len = sprintf(data, "2:0:%s", card);
				send(sockfd, data, data_len, 0);
				send_flag = 0;
			}
			else if (send_flag == 0) //普通打开 需要将"3:card"上传给服务器
			{
				char data[128] = "";
				int data_len = sprintf(data, "3:%s", card);
				send(sockfd, data, data_len, 0);
				//将card发送给tcp_server,如果tcp_server插入数据库成功回复"3:1"或则"3:0"
			}
		}
	}

	pthread_join(recv_tid, NULL);
#endif
	return 0;
}
void *recv_udp_func(void *arg)
{
	while (1)
	{
		char buf[128] = "";
		int len = recv(sockfd, buf, sizeof(buf), 0);
		printf("A53 buf=%s len=%d\n", buf, len);
		//获取卡号的指令“get_card:1”
		if (strncmp(buf, "get_card", 8) == 0)
		{
			printf("A53:%s\n", buf);
			send_flag = 1;
		}
		else if (buf[0] == '3' && buf[2] == '1') //打卡成功
		{
			printf("打卡成功\n");
		}
		else if (buf[0] == '3' && buf[2] == '0') //打卡失败
		{
			printf("打卡失败\n");
		}
	}
}