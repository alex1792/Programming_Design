#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#define MaxLine 8192
#define MaxStudentCnt 256

void *getWord(char *word, char *ptr)
{
    char *qtr = word;
    while (isspace(*ptr))
        ptr++;
    while (!isspace(*ptr) && *ptr != 0)
        *qtr++ = *ptr++;
    *qtr = 0;
    if (strlen(word) == 0)
        return NULL;
    else
        return ptr;
}
int findName(char name[][32], char *word, int studentCnt)
{
    int i;
    for (i = 0; i < studentCnt; i++)
    {
        if (strcmp(name[i], word) == 0)
        {
            break;
        }
    }
    return i;
}

int main()
{
    //  變數與初值
    char line[MaxLine], word[256], name[MaxStudentCnt][32], mathScore[MaxStudentCnt][4], engScore[MaxStudentCnt][4], progScore[MaxStudentCnt][4];
    int studentCnt = 0, state = 0, i = 0;
    line[0] = 0;
    word[0] = 0;
    name[0][0] = 0;
    mathScore[0][0] = '\0';
    engScore[0][0] = '\0';
    progScore[0][0] = '\0';
    //  連續讀入
    while (fgets(line, MaxLine, stdin) != NULL)
    {
        //  判斷功能
        char *ptr = line;
        if (*ptr == 'i')
            state = 1;
        else if (*ptr == 'd')
            state = 2;
        else if (*ptr == 'u')
            state = 3;
        else if (*ptr == 'p')
            state = 4;
        ptr = ptr + 4;
        //  各項功能運作
        switch (state)
        {
        case 1:
            ptr = getWord(name[studentCnt], ptr); //  存名子
            ptr++;
            while (1)
            {
                if (*(ptr) == 'm') //  數學分數
                {
                    ptr += 2;
                    ptr = getWord(mathScore[studentCnt], ptr);
                }
                else if (*(ptr) == 'e') //  英文分數
                {
                    ptr += 2;
                    ptr = getWord(engScore[studentCnt], ptr);
                }
                else if (*(ptr) == 'p') //  程設分數
                {
                    ptr += 2;
                    ptr = getWord(progScore[studentCnt], ptr);
                }
                if (*ptr == '\n')
                    break;
                ptr++;
            }
            studentCnt++;
            break;
        case 2:
            ptr = getWord(word, ptr); //  找名子
            ptr++;
            i = findName(name, word, studentCnt);
            name[i][0] = '\0';
            break;
        case 3:
            ptr = getWord(word, ptr); //  存名子
            ptr++;
            i = findName(name, word, studentCnt);
            while (1)
            {
                if (*ptr == 'm')
                {
                    ptr += 2;
                    ptr = getWord(mathScore[i], ptr);
                }
                else if (*ptr == 'e')
                {
                    ptr += 2;
                    ptr = getWord(engScore[i], ptr);
                }
                else if (*ptr == 'p')
                {
                    ptr += 2;
                    ptr = getWord(progScore[i], ptr);
                }
                if (*ptr == '\n')
                    break;
                ptr++;
            }
            break;
        case 4:
            printf("name\tmathscore\tenglishscore\tprogscore\n");
            int i;
            for (i = 0; i < studentCnt; i++)
            {
                if (strcmp(name[i], "\0") != 0)
                    printf("%s\t%s\t\t%s\t\t%s\n", name[i], mathScore[i], engScore[i], progScore[i]);
            }
            break;
        }
    }
    return 0;
}