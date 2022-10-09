#include <stdio.h>
#include <string.h>
#include <ctype.h>
#define In 1
#define Out 0

int main()
{
    //變數與設定初始值
    char c, longestword[100], upper[26], lower[26], currentWord[100];
    int spaceCnt, whiteSpaceCnt, lowerCaseCnt, upperCaseCnt, digitCaseCnt, caseinsensitiveCnt;
    int byteCnt, wordCnt, lineCnt, upperCnt[26], lowerCnt[26];
    int digitCnt[10], state, i, maxlength = 0, currentlength = 0;
    int currentLineWord = 0;
    state = Out;
    spaceCnt = whiteSpaceCnt = 0;
    lowerCaseCnt = upperCaseCnt = digitCaseCnt = caseinsensitiveCnt = 0;
    byteCnt = wordCnt = lineCnt = 0;
    for (i = 0; i < 26; i++)
    {
        upperCnt[i] = 0;
        lowerCnt[i] = 0;
        digitCnt[i] = 0;
    }
    for (i = 0; i < 100; i++)
    {
        currentWord[i] = '\0';
    }
    // computation
    while ((c = getchar()) != EOF)
    {
        byteCnt++;
        // white space
        if (isspace(c))
        {
            whiteSpaceCnt++;
            state = Out;
        }
        // space
        if (c == ' ')
        {
            spaceCnt++;
            currentLineWord++;
            if (currentlength > maxlength)
            {
                maxlength = currentlength;
                strcpy(longestword, currentWord);
            }
            else if (currentlength == maxlength)
            {
                maxlength = currentlength;
                i = strcmp(currentWord, longestword);
                if (i < 0)
                {
                    strcpy(longestword, currentWord);
                }
            }
            currentlength = 0;
        }
        // Tab
        else if (c == '\t')
        {
            currentLineWord++;
            if (currentlength > maxlength)
            {
                maxlength = currentlength;
                strcpy(longestword, currentWord);
            }
            else if (currentlength == maxlength)
            {
                maxlength = currentlength;
                i = strcmp(currentWord, longestword);
                if (i < 0)
                {
                    strcpy(longestword, currentWord);
                }
            }
            currentlength = 0;
        }
        //大寫
        else if (c - 'A' >= 0 && c - 'Z' <= 0)
        {
            upperCnt[c - 'A']++;
            upperCaseCnt++;
            currentWord[currentlength] = c;
            currentlength++;
            if (state == Out)
            {
                wordCnt++;
                currentLineWord++;
            }
            state = In;
        }
        //小寫
        else if (c - 'a' >= 0 && c - 'z' <= 0)
        {
            lowerCnt[c - 'a']++;
            lowerCaseCnt++;
            currentWord[currentlength] = c;
            currentlength++;
            if (state == Out)
            {
                wordCnt++;
                currentLineWord++;
            }
            state = In;
        }
        // digit
        else if (c - '0' >= 0 && c - '9' <= 0)
        {
            digitCnt[c - '0']++;
            digitCaseCnt++;
            currentWord[currentlength] = c;
            currentlength++;
            if (state == Out)
            {
                wordCnt++;
                currentLineWord++;
            }
            state = In;
        }
        // period句號
        else if (c == '.')
        {
            currentWord[currentlength] = c;
            currentlength++;
            currentLineWord++;
            if (currentlength > maxlength)
            {
                maxlength = currentlength;
                strcpy(longestword, currentWord);
            }
            else if (currentlength == maxlength)
            {
                maxlength = currentlength;
                i = strcmp(currentWord, longestword);
                if (i < 0)
                {
                    strcpy(longestword, currentWord);
                }
            }
            state = In;
        }
        //換行\n
        else if (c == '\n')
        {
            lineCnt++;
            if (currentlength > maxlength)
            {
                maxlength = currentlength;
                strcpy(longestword, currentWord);
            }
            else if (currentlength == maxlength)
            {
                maxlength = currentlength;
                i = strcmp(currentWord, longestword);
                if (i < 0)
                {
                    strcpy(longestword, currentWord);
                }
            }
            currentLineWord = 0;
            currentlength = 0;
        }
        // others其他
        else
        {
            currentWord[currentlength] = c;
            currentlength++;
            if (state == Out)
            {
                wordCnt++;
                currentLineWord++;
            }
            state = In;
        }
    }
    if (currentlength > maxlength)
    {
        maxlength = currentlength;
        strcpy(longestword, currentWord);
    }
    else if (currentlength == maxlength)
    {
        maxlength = currentlength;
        i = strcmp(currentWord, longestword);
        if (i < 0)
        {
            strcpy(longestword, currentWord);
        }
    }
    if (currentLineWord > 0)
    {
        lineCnt++;
    }
    caseinsensitiveCnt = upperCaseCnt + lowerCaseCnt;
    // output
    for (c = 'A'; c <= 'Z'; c++)
    {
        upper[c - 'A'] = c;
    }
    for (c = 'a'; c <= 'z'; c++)
    {
        lower[c - 'a'] = c;
    }
    printf("===\n");
    printf("[0] Overview Stats\n");
    printf("===\n");
    printf("Space Count: %d\n", spaceCnt);
    printf("Whitespace Count: %d\n", whiteSpaceCnt);
    printf("Lowercase Count: %d\n", lowerCaseCnt);
    printf("Uppercase Count: %d\n", upperCaseCnt);
    printf("Digit Count: %d\n", digitCaseCnt);
    printf("Case-insensitive Count: %d\n", caseinsensitiveCnt);
    printf("Byte Count: %d\n", byteCnt);
    printf("Word Count: %d\n", wordCnt);
    printf("Total Line: %d\n", lineCnt);
    printf("===\n");
    printf("[1] Longest Word\n");
    printf("===\n");
    printf("Word: %s\n", longestword);
    printf("Length: %d\n", maxlength);
    printf("===\n");
    printf("[2] Case-Sensitive Stats\n");
    printf("===\n");
    for (i = 0; i < 26; i++)
    {
        printf("%c: %d\t%c: %d\n", upper[i], upperCnt[i], lower[i], lowerCnt[i]);
    }
    printf("===\n");
    printf("[3] Case-Insensitive Stats\n");
    printf("===\n");
    for (i = 0; i < 26; i++)
    {
        printf("%c: %d\n", lower[i], upperCnt[i] + lowerCnt[i]);
    }
    printf("===\n");
    printf("[4] Digit Stats\n");
    printf("===\n");
    for (i = 0; i <= 9; i++)
    {
        printf("%d: %d\n", i, digitCnt[i]);
    }
    return 0;
}
