#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "sqlite3.h"
int main(int argc, char const *argv[])
{
    printf("content-type:textml\n\n");
    //获取收到的数据(url中？后面的数据)
    char *data = getenv("QUERY_STRING");
    //printf("%s\n", data);
#if 1
    //char *data = "root:123456";
    char usr[125] = "";
    char pwd[125] = "";
    sscanf(data, "%[^:]:%s", usr, pwd);
    //获取数据库中的数据
    sqlite3 *db = NULL;
    int ret = sqlite3_open("../door.db", &db);
    if (ret != SQLITE_OK)
    {
        perror("sqlite3_open");
        return 0;
    }

    //查询lucy的信息
    char sql[128] = "";
    sprintf(sql, "select * from user where user=\'%s\';", usr);
    //printf("sql=%s\n", sql);
    // sqlite3_exec(db, sql, my_fun, NULL, NULL);
    char **result = NULL;
    int row = 0, col = 0;
    sqlite3_get_table(db, sql, &result, &row, &col, NULL);
    //printf("row=%d, col=%d\n", row, col);
    if (row >= 1)
    {
        // result[5] 表明数据库中存放的密码
        if (strcmp(result[5], pwd) != 0)
        {
            printf("0");
        }
        else
        {
            if(strcmp(result[7],"root")==0)
                printf("root");
            else if(strcmp(result[7],"user")==0)
                printf("user");
        }
    }
    else
    {
        printf("0");
    }
    // 记录登录用户名
    memset(sql, 0, sizeof(sql));
    sprintf(sql, "UPDATE tmp_user SET user =\'%s\',pwd=\'%s\';", usr, pwd);
    sqlite3_exec(db, sql, NULL, NULL, NULL);
    //关闭数据库
    sqlite3_close(db);
#endif
    return 0;
}