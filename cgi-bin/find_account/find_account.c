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
    char pwd[32] = "";
    char type_pwd[128] = "";
    // 获取收到的数据(url中？后面的数据)
    sscanf(data, "%[^:]:%s", user, type_pwd);
    sscanf(type_pwd, "%[^:]:%s", type, pwd);
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
    // 判断账户密码是否正确
    if (strcmp(type, "name") == 0)
        sprintf(sql, "SELECT * FROM account WHERE user=\'%s\';", user);
    else if (strcmp(type, "id") == 0)
        sprintf(sql, "SELECT * FROM account WHERE card=\'%s\';", user);
    char **check_result = NULL;
    int i = 0, j = 0;
    int row = 0, col = 0;
    sqlite3_get_table(db, sql, &check_result, &row, &col, NULL);
    if (row >= 0)
    {
        if (strcmp(check_result[5], pwd) != 0)
        {
            printf("0");
        }
        // 账户通过
        else
        {
            if (strcmp(type, "name") == 0)
                sprintf(sql, "SELECT user, card, money FROM account WHERE user=\'%s\';", user);
            else if (strcmp(type, "id") == 0)
                sprintf(sql, "SELECT user, card, money FROM account WHERE card=\'%s\';", user);
            char **result = NULL;
            row = 0, col = 0;
            sqlite3_get_table(db, sql, &result, &row, &col, NULL);

            char buf[1024] = "<table border='2'>";
            for (i = 0; i < row + 1; i++)
            {
                strcat(buf, "<tr>");
                for (j = 0; j < col; j++)
                {
                    strcat(buf, "<td>");
                    strcat(buf, result[i * col + j]); // 存放的就是查找结果
                    strcat(buf, "</td>");
                }
                strcat(buf, "</tr>");
            }
            strcat(buf, "</table>");

            printf("%s", buf);
        }
    }
    else
    {
        // 账户密码不正确
        printf("0");
    }
    // 关闭数据库
    sqlite3_close(db);
#endif
    close(sockfd);
    return 0;
}
