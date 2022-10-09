#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#define MaxLine 1025

void Usage()
{
    printf("Usage:\n");
    printf("./sed [-g(optional)] [-source(required)] [-target(required)]\n");
}

int main(int argc, char **argv)
{
    //  變數
    char line[MaxLine];
    char *pos = NULL;
    char *ptr = NULL;
    int sourceLen = 0;
    line[0] = 0;

    while (fgets(line, MaxLine, stdin) != NULL)
    {
        pos = line;
        //  無參數
        if (argc == 3)
        {
            sourceLen = strlen(argv[1]);
            if ((ptr = strstr(line, argv[1])) != NULL) // 無參數 只改第一個
            {
                while (ptr - pos > 0)
                {
                    printf("%c", *pos);
                    pos++;
                }
                pos += sourceLen;
                printf("%s", argv[2]);
                while (*pos != '\0')
                {
                    printf("%c", *pos);
                    pos++;
                }
                // printf("\n");
            }
            else
            {
                printf("%s", line);
            }
        }
        //  有參數
        else if (argc == 4)
        {
            //  參數下錯
            if (strcmp(argv[1], "-g") != 0)
            {
                Usage();
                return 0;
            }
            //  正確
            else
            {
                sourceLen = strlen(argv[2]);
                while ((ptr = strstr(pos, argv[2])) != NULL)
                {
                    while (ptr - pos > 0)
                    {
                        printf("%c", *pos);
                        pos++;
                    }
                    printf("%s", argv[3]);
                    pos += sourceLen;
                }
                // printf("1");
                while (*pos != '\0')
                {
                    printf("%c", *pos);
                    pos++;
                }
            }
        }
        //  必須輸入的資料不夠
        else
        {
            Usage();
            return 0;
        }
    }

    return 0;
}