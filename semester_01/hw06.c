#include <stdio.h>
#include <ctype.h>
#include <string.h>

int main()
{
    // variabls and initials
    char word[1024][101], line[8192];
    char firstWord[101];
    char *token;
    char repetedSentence[100][8192], originalSentnece[100][8192];
    char longestWord[100][101];
    char cutWord[] = " \n\v\f\r\t.,?!\"():";
    int totalWord, repetedLineCnt, currentWordLength, maxWordLength;
    int i, j, k, w, p, q, r;
    i = j = k = w = p = q = r = 0;
    firstWord[0] = '\0';
    currentWordLength = 0;
    maxWordLength = 0;
    totalWord = 0;
    repetedLineCnt = 0;

    while (fgets(line, 8192, stdin))
    {
        if (strcmp(line, "\n") == 0)
        {
            continue;
        }
        strcpy(originalSentnece[k], line);
        strcpy(repetedSentence[k], line);
        // copy first word
        token = strtok(repetedSentence[k], cutWord);
        strcpy(firstWord, token);
        strcpy(word[w], token);
        totalWord++;
        // length
        currentWordLength = strlen(firstWord);
        if (currentWordLength > maxWordLength)
        {
            maxWordLength = currentWordLength;
            j = 0;
            strcpy(longestWord[j], word[w]);
            w++;
            j++;
        }
        else if (currentWordLength == maxWordLength)
        {
            for (i = 0; i < j; i++)
            {
                if (strcmp(longestWord[i], word[w]) == 0)
                {
                    r++;
                }
            }
            if (r == 0)
            {
                strcpy(longestWord[j], word[w]);
                j++;
            }
            w++;
        }
        else
        {
            w++;
        }
        // other words
        while (1)
        {
            token = strtok(NULL, cutWord);
            if (token == NULL)
            {
                if (repetedLineCnt == 0)
                {
                    repetedSentence[k][0] = '\0';
                }
                else
                {
                    k++;
                }
                repetedLineCnt = 0;
                break;
            }
            else
            {
                strcpy(word[w], token);
                currentWordLength = strlen(token);
                if (strcmp(firstWord, word[w]) == 0)
                {
                    repetedLineCnt++;
                }
                if (currentWordLength > maxWordLength)
                {
                    maxWordLength = currentWordLength;
                    j = 0;
                    strcpy(longestWord[j], word[w]);
                    w++;
                    j++;
                }
                else if (currentWordLength == maxWordLength)
                {
                    for (i = 0; i < j; i++)
                    {
                        if (strcmp(longestWord[i], word[w]) == 0)
                        {
                            r++;
                        }
                    }
                    if (r == 0)
                    {
                        strcpy(longestWord[j], word[w]);
                        j++;
                    }
                    w++;
                }
                else
                {
                    w++;
                }
                totalWord++;
            }
        }
    }

    // output
    printf("--- [0] The line that the first word occurs more than twice in the line ---\n");
    if (k > 0)
    {
        printf("Repeated line count: %d\n", k);
        for (i = 0; i < k; i++)
        {
            printf("[%d]: %s", i, originalSentnece[i]);
            // if(i == k - 1) {
            // printf("\n");
            //}
        }
    }
    else
    {
        printf("It is not exist!\n");
    }
    printf("--- [1] The longest words and their length ---\n");
    printf("Word length: %d\n", maxWordLength);
    for (i = 0; i < j; i++)
    {
        printf("[%d]: %s", i, longestWord[i]);
        if (i <= j - 1)
        {
            printf("\n");
        }
    }
    printf("--- [2] The words appear in the article ---\n");
    printf("Total words: %d\n", totalWord);
    for (i = 0; i < totalWord; i++)
    {
        printf("%s ", word[i]);
        if ((i - 9) % 10 == 0)
        {
            printf("\n");
        }
    }
    return 0;
}