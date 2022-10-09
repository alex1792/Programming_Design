#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#define MaxWord 256

//  預設小到大
void bubbleSort(char **array, int cnt)
{
    int i, j;
    char *tmp = malloc(sizeof(char) * 64);
    for (i = 0; i < cnt; i++)
    {
        for (j = 0; j < cnt - 1 - i; j++)
        {
            if (strcmp(*(array + j), *(array + j + 1)) > 0)
            {
                strcpy(tmp, *(array + j));
                strcpy(*(array + j), *(array + j + 1));
                strcpy(*(array + j + 1), tmp);
            }
        }
    }
    free(tmp);
    tmp = NULL;
}
//  小到大
void bubbleSort1(char **array, int cnt)
{
    int i, j;
    char *tmp = malloc(sizeof(char) * 64);
    for (i = 0; i < cnt; i++)
    {
        for (j = 0; j < cnt - 1 - i; j++)
        {
            if (atoi(*(array + j)) > atoi(*(array + j + 1)))
            {
                strcpy(tmp, *(array + j));
                strcpy(*(array + j), *(array + j + 1));
                strcpy(*(array + j + 1), tmp);
            }
        }
    }
    free(tmp);
    tmp = NULL;
}
int main(int argc, char **argv)
{
    //  變數與初始值
    int i, errorCnt, wordCnt, state, usageCnt;
    char **word = malloc(sizeof(char *) * MaxWord);
    char *input = malloc(sizeof(char) * MaxWord);
    errorCnt = 0;
    usageCnt = 0;
    wordCnt = 0;
    state = 0;
    //  讀取資料
    while (scanf("%s", input) != EOF)
    {
        //  配空間並把input存到word指標陣列裡
        *(word + wordCnt) = malloc(sizeof(char) * (strlen(input) + 1));
        strcpy(*(word + wordCnt), input);
        wordCnt++;
    }
    //  預設 沒下任何參數的時候 bubbleSort(小到大)
    if (argc == 1)
    {
        bubbleSort(word, wordCnt);
    }
    //  做參數之指令
    for (i = 1; i < argc; i++)
    {
        //  -h 印出usage
        if (strcmp(*(argv + i), "-h") == 0)
        {
            printf("Usage:\n");
            printf("\t-h --help usage\n\t-n numerical\n\t-r reverse\n");
            usageCnt++;
        }
        //  -n 數值比較 只有數字做排序 由小到大 (文字->數字)
        else if (strcmp(*(argv + i), "-n") == 0)
        {
            bubbleSort1(word, wordCnt);
        }
        //  -r 反向輸出
        else if (strcmp(*(argv + i), "-r") == 0)
        {
            bubbleSort(word, wordCnt);
            state = 1;
        }
        //  非參數 印出錯誤訊息
        else
        {
            printf("Undefined parameter: %s.\n", *(argv + i));
            errorCnt++;
        }
    }
    //  有非參數 印出Usage
    if (errorCnt > 0)
    {
        printf("Usage:\n");
        printf("\t-h --help usage\n\t-n numerical\n\t-r reverse\n");
    }
    //  輸出
    else
    {
        //  正常
        if (state != 1 && usageCnt == 0)
        {
            for (i = 0; i < wordCnt; i++)
            {
                printf("%s\n", *(word + i));
            }
        }
        //  反向輸出
        else if (state == 1 && usageCnt == 0)
        {
            for (i = wordCnt - 1; i >= 0; i--)
            {
                printf("%s\n", *(word + i));
            }
        }
    }
    free(word);
    free(input);
    word = NULL;
    input = NULL;
    return 0;
}