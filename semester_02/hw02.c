#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#define MaxName 33
#define MaxEmail 129
#define MaxUrl 129
#define MaxPhone 16
#define MaxPeople 128
#define MaxLine 1024
struct List
{
    char name[MaxName];
    char email[MaxEmail];
    char url[MaxUrl];
    char phone[MaxPhone];
};

//  i)更新  d)刪除  f)找尋  s)排序  p)印出
//  <參數>\t<name>\t<email>\t<url>\t<phone_number>

void create(struct List addr[], int idx, char *line)
{
    char *qtr = NULL;
    char *ptr = line;
    char copy[MaxName];
    copy[0] = '\0';
    qtr = copy;

    for (int i = 0; i < 4; i++)
    {
        while (*ptr != '\t' && *ptr != '\0')
        {
            *qtr++ = *ptr++;
        }
        *qtr = '\0';
        if (i == 0)
        {
            strcpy(addr[idx].name, copy);
        }
        else if (i == 1)
        {
            strcpy(addr[idx].email, copy);
        }
        else if (i == 2)
        {
            strcpy(addr[idx].url, copy);
        }
        else if (i == 3)
        {
            strcpy(addr[idx].phone, copy);
        }
        copy[0] = '\0';
        qtr = copy;
        ptr++;
    }
}

void update(struct List addr[], int idx, char *line)
{
    char space[MaxName];
    char *ptr = line;
    char *qtr = space;
    int i;
    // ptr += 2;
    while (*ptr != '\t')
    {
        *qtr++ = *ptr++;
    }
    *qtr = 0;
    ptr++;
    for (i = 0; i < idx; i++)
    {
        if (strcmp(addr[i].name, space) == 0)
        {
            for (int j = 0; j < 3; j++)
            {
                space[0] = 0;
                qtr = space;
                while (*ptr != '\t' && *ptr != '\0')
                {
                    *qtr++ = *ptr++;
                }
                *qtr = 0;
                ptr++;
                if (j == 0)
                {
                    strcpy(addr[i].email, space);
                }
                else if (j == 1)
                {
                    strcpy(addr[i].url, space);
                }
                else if (j == 2)
                {
                    strcpy(addr[i].phone, space);
                }
            }
        }
    }
}

void delete (struct List addr[], int idx, char *line)
{
    char tmp[MaxName];
    char *ptr = line;
    char *qtr = tmp;
    tmp[0] = 0;
    while (*ptr != '\n')
    {
        *qtr++ = *ptr++;
    }
    *qtr = 0;
    for (int i = 0; i < idx; i++)
    {
        if (strcmp(addr[i].name, tmp) == 0)
        {
            for (int j = i; j < idx - 1; j++)
            {
                strcpy(addr[j].name, addr[j + 1].name);
                strcpy(addr[j].email, addr[j + 1].email);
                strcpy(addr[j].url, addr[j + 1].url);
                strcpy(addr[j].phone, addr[j + 1].phone);
            }
        }
    }
}

void find(struct List addr[], int idx, char *line)
{
    char tmp[MaxName];
    char *ptr = line;
    char *qtr = tmp;
    int flag = 0;
    tmp[0] = 0;
    while (*ptr != '\n')
    {
        *qtr++ = *ptr++;
    }
    *qtr = 0;
    for (int i = 0; i < idx; i++)
    {
        if (strstr(addr[i].name, tmp) != NULL)
        {
            flag++;
            if (flag == 1)
            {
                printf("Find %s result: ", tmp);
            }
            printf("%s ", addr[i].name);
        }
    }
    if (flag > 0)
    {
        printf("\n");
    }
    else
    {
        printf("%s not found!\n", tmp);
    }
}

void swap(struct List addr[], int j)
{
    struct List tmp;
    tmp = addr[j];
    addr[j] = addr[j + 1];
    addr[j + 1] = tmp;
}

void sort(struct List addr[], int cnt, char *linePtr)
{
    if (*linePtr == 'n')
    {
        for (int i = 0; i < cnt; i++)
        {
            for (int j = 0; j < cnt - 1 - i; j++)
            {
                if (strcmp(addr[j].name, addr[j + 1].name) > 0)
                {
                    swap(addr, j);
                }
            }
        }
    }
    else if (*linePtr == 'e')
    {
        for (int i = 0; i < cnt; i++)
        {
            for (int j = 0; j < cnt - 1 - i; j++)
            {
                if (strcmp(addr[j].email, addr[j + 1].email) > 0)
                {
                    swap(addr, j);
                }
            }
        }
    }
    else if (*linePtr == 'u')
    {
        for (int i = 0; i < cnt; i++)
        {
            for (int j = 0; j < cnt - 1 - i; j++)
            {
                if (strcmp(addr[j].url, addr[j + 1].url) > 0)
                {
                    swap(addr, j);
                }
            }
        }
    }
    else
    {
        for (int i = 0; i < cnt; i++)
        {
            for (int j = 0; j < cnt - 1 - i; j++)
            {
                if (atoi(addr[j].phone) > atoi(addr[j + 1].phone))
                {
                    swap(addr, j);
                }
            }
        }
    }
}

void print(struct List addr[], int cnt)
{
    printf("number\tname\temail\tsite\tphone number\n");
    printf("----------------------------------------------------\n");
    for (int i = 0; i < cnt; i++)
    {
        printf("[%d] %s\t%s\t%s\t%s", i + 1, addr[i].name, addr[i].email, addr[i].url, addr[i].phone);
    }
    printf("\n");
}
int main(int argc, char **argv)
{
    struct List addr[MaxPeople];
    int time = atoi(argv[1]);
    int cnt = 0;
    char line[MaxLine];
    char *linePtr = NULL;

    //  建立第一筆資料
    for (int i = 0; i < time; i++)
    {
        fgets(line, MaxLine, stdin);
        create(addr, cnt, line);
        cnt++;
    }

    //  互動模式
    while (fgets(line, MaxLine, stdin) != NULL)
    {
        linePtr = line;
        linePtr += 2;
        //  新增
        if (line[0] == 'i')
        {
            // linePtr += 2;
            create(addr, cnt, linePtr);
            cnt++;
        }
        //  更新
        else if (line[0] == 'u')
        {
            update(addr, cnt, linePtr);
        }
        //  刪除
        else if (line[0] == 'd')
        {
            delete (addr, cnt, linePtr);
            cnt--;
        }
        //  找尋
        else if (line[0] == 'f')
        {
            find(addr, cnt, linePtr);
        }
        //  排序
        else if (line[0] == 's')
        {
            sort(addr, cnt, linePtr);
        }
        //  印出
        else if (line[0] == 'p')
        {
            print(addr, cnt);
        }
        //  離開
        else if (line[0] == 'q')
        {
            break;
        }
    }
    return 0;
}