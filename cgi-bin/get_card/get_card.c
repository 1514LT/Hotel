#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include "sqlite3.h"
int sockfd = 0;
int main(int argc, char const *argv[])
{
    printf("content-type:textml\n\n");
    // 获取收到的数据(url中？后面的数据)
    char *data = getenv("QUERY_STRING");
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
    send(sockfd, "1:0", 3, 0);
    sleep(1);
    // 4、发送"get_card:设备号"指令
    send(sockfd, "get_card:1", 10, 0);
    // 5、获取服务器的应答
    char card[128] = "";
    recv(sockfd, card, sizeof(card), 0);
    printf("%s",card);
    close(sockfd);
    return 0;
}