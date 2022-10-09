#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#define MaxWord 1025
struct term
{
    char word[MaxWord];
    int cnt;
    struct term *next;
};

void standardlization(char *word)
{
    int len = strlen(word);
    int i = 0;
    if (word[0] == '-')
    {
        for (i = 1; i < len - 1; i++)
        {
            word[i - 1] = word[i];
            // printf("%c\n", word[i]);
        }
        word[i - 1] = '\0';
    }
    else
    {
        if (word[len - 1] == '\n')
        {
            word[len - 1] = '\0';
        }
    }
}

void creatList(struct term *head, char *line)
{
    strcpy(head->word, line);
    head->cnt = 1;
    head->next = NULL;
}

struct term *find(struct term *head, char *line)
{
    struct term *tmp;
    tmp = head;
    while (tmp)
    {
        if (strcmp(tmp->word, line) == 0)
        {
            // printf("found!\n");
            return tmp;
        }
        else
        {
            tmp = tmp->next;
        }
    }
    return NULL;
}

void insert(struct term *head, char *line)
{
    struct term *latest, *tmp;
    latest = (struct term *)malloc(sizeof(struct term));
    strcpy(latest->word, line);
    latest->cnt = 1;
    latest->next = NULL;
    // printf("%s: %d\n", new->word, new->cnt);
    // printf("inserted successfully!\n");
    tmp = head;
    while (tmp->next != NULL)
    {
        tmp = tmp->next;
    }
    tmp->next = latest;
    // printf("inserted successfully!\n");
}

void print(struct term *head)
{
    struct term *tmp;
    tmp = head;
    while (tmp->next != NULL)
    {
        printf("%s: %d\n", tmp->word, tmp->cnt); // Print data of current node
        tmp = tmp->next;                         // Move to next node
    }
    printf("%s: %d\n", tmp->word, tmp->cnt); //  漏掉最後一個
}

void freeAll(struct term *head)
{
    struct term *cur, *prev;
    cur = head;
    while (cur->next != NULL)
    {
        prev = cur;
        cur = cur->next;
        free(prev);
    }
    free(cur); //最後一個要free掉
}
int main()
{
    char line[MaxWord];
    struct term *head = (struct term *)malloc(sizeof(struct term));
    int i = 1;
    while (fgets(line, MaxWord, stdin) != NULL)
    {
        if (line[0] != '-') //  新增或重複
        {
            standardlization(line); //  移除換行符號
            if (strlen(line) > 0)
            {
                if (i == 1) //  建立 linked list
                {
                    creatList(head, line);
                    i++;
                }
                else //  比對後新增或著重複cnt++
                {
                    if (find(head, line) == NULL) //  沒找到 要建立新的節點
                    {
                        insert(head, line);
                    }
                    else //  有找到 cnt++
                    {
                        find(head, line)->cnt += 1;
                    }
                }
            }
        }
        else //  有'-'
        {
            standardlization(line);
            if (find(head, line) != NULL)
            {
                find(head, line)->cnt--;
            }
        }
    }
    print(head);
    freeAll(head);
    return 0;
}