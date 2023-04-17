#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "sqlite3.h"
int main(int argc, char const *argv[])
{
    printf("content-type:textml\n\n");
    // 获取收到的数据(url中？后面的数据)
    char *data = getenv("QUERY_STRING");

    // char *data = "1514";
    char key[32] = "";
    char tmp[32] = "";
    sscanf(data, "%[^:]:%s", key, tmp);
#if 1
    // 获取数据库中的数据
    sqlite3 *db = NULL;
    int ret = sqlite3_open("../door.db", &db);
    if (ret != SQLITE_OK)
    {
        perror("sqlite3_open");
        return 0;
    }

    // 验证是否重复设置key

    char sql[128] = "";
    sprintf(sql, "SELECT * FROM key WHERE key=\'%s\';", key);
    char **result = NULL;
    int row = 0, col = 0;
    sqlite3_get_table(db, sql, &result, &row, &col, NULL);
    if (row >= 1)//有重复数据
    {
        printf("repeat");
    }
    else{
        memset(sql, 0, sizeof(sql));
        sprintf(sql, "INSERT INTO key VALUES (1,\'%s\');", key);

        sqlite3_exec(db, sql, NULL, NULL, NULL);
        printf("ok");
    }
        // 关闭数据库
        sqlite3_close(db);
#endif
    return 0;
}