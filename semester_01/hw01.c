#include <stdio.h>
#include <string.h>

int main()
{
    char input[101];
    while (scanf("%s", input) != EOF)
    {
        if (strcmp(input, "cat") == 0)
        {
            printf("貓\n");
        }
        else if (strcmp(input, "dog") == 0)
        {
            printf("狗\n");
        }
        else if (strcmp(input, "banana") == 0)
        {
            printf("香蕉\n");
        }
        else if (strcmp(input, "pineapple") == 0)
        {
            printf("鳳梨\n");
        }
        else if (strcmp(input, "computer") == 0)
        {
            printf("電腦\n");
        }
        else if (strcmp(input, "key") == 0)
        {
            printf("鑰匙\n");
        }
        else if (strcmp(input, "code") == 0)
        {
            printf("程式\n");
        }
        else if (strcmp(input, "flunk") == 0)
        {
            printf("當掉\n");
        }
        else if (strcmp(input, "array") == 0)
        {
            printf("陣列\n");
        }
        else
        {
            printf("這啥鬼?\n");
        }
    }
    return 0;
}