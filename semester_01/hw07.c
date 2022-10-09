#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

//  getWord
char *getWord(char *word, char *ptr)
{
    char *qtr = word;
    while (isspace(*ptr))
    {
        ptr++;
    }
    while (!isspace(*ptr))
    {
        *qtr++ = *ptr++;
    }
    *qtr = 0;
    if (strlen(word) == 0)
    {
        return NULL;
    }
    else
    {
        return ptr;
    }
}

//  intBubbleSort
void intBubbleSort(int num[], int numCnt)
{
    int i, j;
    for (i = 0; i < numCnt; i++)
    {
        for (j = 0; j < numCnt - i - 1; j++)
        {
            if (num[j] < num[j + 1])
            {
                int tmp = num[j];
                num[j] = num[j + 1];
                num[j + 1] = tmp;
            }
        }
    }
    for (i = 0; i < numCnt; i++)
    {
        printf("%d\n", num[i]);
    }
}

//  wordSort
void wordSort(char word[][256], int wordCnt)
{
    int i, j;
    //  bubbleSort
    for (i = 0; i < wordCnt; i++)
    {
        for (j = 0; j < wordCnt - 1 - i; j++)
        {
            if (word[j][0] > word[j + 1][0])
            {
                char tmp[128];
                tmp[0] = 0;
                strcpy(tmp, word[j]);
                strcpy(word[j], word[j + 1]);
                strcpy(word[j + 1], tmp);
                tmp[0] = 0;
            }
        }
    }
    //  輸出
    for (i = 0; i < wordCnt; i++)
    {
        printf("%s\n", word[i]);
    }
}

int main()
{
    int num[256], wordCnt = 0, numCnt = 0, state = 2;
    char word[256], words[256][256];
    char line[1024];
    char *ptr;
    //  初始值
    num[0] = '\0';
    line[0] = '\0';
    word[0] = '\0';
    words[0][0] = '\0';
    //  讀一行 讀到結束為止
    while (fgets(line, 1024, stdin) != NULL)
    {
        ptr = line;
        while ((ptr = getWord(word, ptr)) != NULL)
        {
            //  是正整數 並儲存
            if (atoi(word) > 0)
            {
                num[numCnt] = atoi(word);
                numCnt++;
            }
            //  是0或著字串
            else if (atoi(word) == 0)
            {
                //  是0 不儲存 將word清空
                if (word[0] == '0')
                {
                    word[0] = '\0';
                    continue;
                }
                //  是字串
                else
                {
                    int i;
                    for (i = 0; i < wordCnt; i++)
                    {
                        state = 0;
                        //  判斷是否重複 重複則state = 1 不重複state = 2
                        if (strcmp(words[i], word) == 0)
                        {
                            state = 1;
                            word[0] = '\0';
                            break;
                        }
                    }
                    //  不重複 儲存至string陣列
                    if (state != 1)
                    {
                        strcpy(words[wordCnt], word);
                        words[wordCnt][strlen(words[wordCnt])] = '\0';
                        wordCnt++;
                    }
                    state = 2;
                }
            }
            word[0] = '\0';
        }
        line[0] = '\0';
    }
    if (wordCnt > 0)
    {
        wordSort(words, wordCnt);
    }
    if (numCnt > 0)
    {
        intBubbleSort(num, numCnt);
    }
    return 0;
}