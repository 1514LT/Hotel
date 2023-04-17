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
    char *data = getenv("QUERY_STRING");
    // 这里的user代表输入的是用户名或者卡号id！
    char user[64] = "";
    char type[32] = "";
    // 获取收到的数据(url中？后面的数据)
    sscanf(data, "%[^:]:%s", user, type);
#if 1
    // 获取数据库中的数据
    sqlite3 *db = NULL;
    int ret = sqlite3_open("../door.db", &db);
    if (ret != SQLITE_OK)
    {
        perror("sqlite3_open");
        return 0;
    }
    char sql[128] = "";

    char **check_result = NULL;
    int row = 0, col = 0;
    sprintf(sql, "SELECT * FROM user WHERE user=\'%s\';", user);
    sqlite3_get_table(db, sql, &check_result, &row, &col, NULL);
    if(row>=1)
    {
        //用户存在，更新权限
        memset(sql,0,sizeof(sql));
        if (strcmp(type, "user") == 0)
            sprintf(sql, "UPDATE user SET permission='root' WHERE user=\'%s\';", user);
        else if (strcmp(type, "root") == 0)
            sprintf(sql, "UPDATE user SET permission='user' WHERE user=\'%s\';", user);
        sqlite3_exec(db, sql, NULL, NULL, NULL);
        printf("修改成功");
    }
    else{
        printf("用户不存在");
    }
    // 关闭数据库
    sqlite3_close(db);
#endif
    close(sockfd);
    return 0;
}
