#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#define MaxWord 1025

struct term //  結構
{
    char word[MaxWord];
    int cnt;
    struct term *next;
};

void standardlization(char *word) //  字串標準化
{
    int len = strlen(word);
    int i = 0;
    if (word[0] == '-') //  去除'-'
    {
        for (i = 1; i < len - 1; i++)
        {
            word[i - 1] = word[i];
        }
        word[i - 1] = '\0';
    }
    else //  去除'\n'
    {
        if (word[len - 1] == '\n')
        {
            word[len - 1] = '\0';
        }
    }
}

void creatList(struct term *head, char *line) //  建立第一個節點
{
    strcpy(head->word, line);
    head->cnt = 1;
    head->next = NULL;
}

struct term *find(struct term *head, char *line) //  尋找每個節點的word並比對
{
    struct term *tmp;
    tmp = head;
    while (tmp)
    {
        if (strcmp(tmp->word, line) == 0) //  有找到 回傳位置
        {
            return tmp; //  回傳位置
        }
        else
        {
            tmp = tmp->next; //  繼續找
        }
    }
    return NULL; //  沒找到 回傳NULL
}

void insert(struct term *head, char *line) //  insert at tail
{
    struct term *latest, *tmp;
    latest = (struct term *)malloc(sizeof(struct term)); //  要新增的節點
    strcpy(latest->word, line);                          //  存資料
    latest->cnt = 1;
    latest->next = NULL;
    tmp = head;
    while (tmp->next != NULL) //  從頭開始找並找到最後一個
    {
        tmp = tmp->next;
    }
    tmp->next = latest; //  把新的節點連接上
}

void print(struct term *head) //  印出
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

void freeAll(struct term *head) //  釋放記憶體
{
    struct term *cur, *prev;
    cur = head;
    while (cur->next != NULL)
    {
        prev = cur;
        cur = cur->next;
        free(prev);
    }
    free(cur); //   最後一個要free掉
}

void List2Array(struct term *head, struct term *sorted) //  linked list to array
{
    struct term *tmp = head;
    int i = 0;
    while (tmp->next != NULL)
    {
        strcpy(sorted[i].word, tmp->word);
        sorted[i].cnt = tmp->cnt;
        i++;
        tmp = tmp->next;
    }
    strcpy(sorted[i].word, tmp->word); //  最後一個
    sorted[i].cnt = tmp->cnt;
}

int cmp(const void *a, const void *b) //  qsort比較函式
{
    return (*(struct term *)a).cnt - (*(struct term *)b).cnt;
}

int main(int argc, char **argv)
{
    char line[MaxWord];
    struct term sorted[MaxWord];
    struct term *head = (struct term *)malloc(sizeof(struct term));
    int cnt = 0;
    while (fgets(line, MaxWord, stdin) != NULL)
    {
        if (line[0] != '-') //  新增或重複
        {
            standardlization(line); //  移除換行符號
            if (strlen(line) > 0)
            {
                if (cnt == 0) //  建立 linked list
                {
                    creatList(head, line);
                    cnt++;
                }
                else //  比對後新增或著重複cnt++
                {
                    if (find(head, line) == NULL) //  沒找到 要建立新的節點
                    {
                        insert(head, line);
                        cnt++;
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
    List2Array(head, sorted);
    qsort(sorted, cnt, sizeof(struct term), cmp); //排序cnt會由小到大
    if (strcmp(argv[1], "asc") == 0)              // cnt由小到大
    {
        for (int i = 0; i < cnt; i++)
        {
            printf("%s: %d\n", sorted[i].word, sorted[i].cnt);
        }
    }
    else
    { // cnt由大到小
        for (int i = cnt - 1; i >= 0; i--)
        {
            printf("%s: %d\n", sorted[i].word, sorted[i].cnt);
        }
    }
    freeAll(head);
    return 0;
}