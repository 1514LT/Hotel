#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "sqlite3.h"
int main(int argc, char const *argv[])
{
#if 1
    printf("content-type:textml\n\n");
    // 获取收到的数据(url中？后面的数据)
    char *data = getenv("QUERY_STRING");

    char usr[64] = "";
    char pwd[64] = "";
    sscanf(data, "%[^:]:%s", usr, pwd);

    // 获取数据库中的数据
    sqlite3 *db = NULL;
    int ret = sqlite3_open("../door.db", &db);
    if (ret != SQLITE_OK)
    {
        perror("sqlite3_open");
        return 0;
    }

    // 查询lucy的信息
    char sql[128] = "select * from tmp_user";
    char **result = NULL;
    int row = 0, col = 0;
    sqlite3_get_table(db, sql, &result, &row, &col, NULL);
    if (row >= 1)
    {
        printf("%s", result[4]);
    }
    else
    {
        printf("0");
    }

    // 关闭数据库
    sqlite3_close(db);
#endif
    return 0;
}
