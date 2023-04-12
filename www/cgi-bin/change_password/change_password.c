#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "sqlite3.h"
int main(int argc, char const *argv[])
{
    printf("content-type:textml\n\n");
    // 获取收到的数据(url中？后面的数据)
    char *data = getenv("QUERY_STRING");

    // char *data = "root:123456:111111";
    char usr[64] = "";
    char pwd[64] = "";
    char new_pwd[64] = "";
    char tmp[64] = "";
    sscanf(data, "%[^:]:%s", usr, tmp);
    sscanf(tmp, "%[^:]:%s", pwd, new_pwd);
    // printf("user:%s pwd:%s new_pwd:%s", usr, pwd, new_pwd);
#if 1
    // 获取数据库中的数据
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
    // char **change_result = NULL;
    int row = 0, col = 0;
    sqlite3_get_table(db, sql, &result, &row, &col, NULL);
    //printf("row=%d, col=%d\n", row, col);
    if (row >= 1)
    {
        // result[5] 表明数据库中存放的密码
        if (strcmp(result[5], pwd) != 0)//密码不匹配
        {
            printf("pwd_erro");
        }
        else//密码匹配，修改密码
        {
            memset(sql,0,sizeof(sql));
            sprintf(sql, "UPDATE user SET pwd=\'%s\' WHERE user=\'%s\';", new_pwd,usr);
            sqlite3_exec(db, sql, NULL, NULL, NULL);
            printf("ok");
        }
    }
    else
    {
        printf("0");
    }

    //关闭数据库
    sqlite3_close(db);
#endif
    return 0;
}