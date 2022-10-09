#include <stdio.h>

int main()
{
    int n, m; // n為縱 m為橫
    int i, j;
    while (scanf("%d %d", &n, &m) != EOF)
    {
        printf("*\t"); //印出左上角的*
        for (i = 1; i <= m; i++)
        { //印出最上列
            printf("%d\t", i);
        }
        printf("\n");

        for (i = 1; i <= n; i++)
        {
            printf("%d\t", i); //印出第一列
            for (j = 1; j <= m; j++)
            {
                printf("%d\t", i * j);
            }
            printf("\n");
        }
    }
    return 0;
}