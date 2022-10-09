#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#define Max 65

struct Tnode
{
    char word[Max];
    int cnt;
    struct Tnode *l_child;
    struct Tnode *r_child;
};

struct Tnode *BSTfind(struct Tnode *root, char *line)
{
    if (root == NULL)
        return NULL;
    if (strcmp(line, root->word) > 0)
        BSTfind(root->r_child, line);
    else if (strcmp(line, root->word) < 0)
        BSTfind(root->l_child, line);
    else
        return root;
}

struct Tnode *insert(struct Tnode *root, char *line)
{
    // if(strlen(line) <= 1)   return;
    // printf("malloced!\n");
    struct Tnode *tmp = malloc(sizeof(struct Tnode));
    struct Tnode *current, *parent;

    strcpy(tmp->word, line);
    tmp->cnt = 1;
    tmp->l_child = NULL;
    tmp->r_child = NULL;

    if (root == NULL)
        return tmp; // creat root
    else
    {
        current = root;
        parent = NULL;
    }

    while (1)
    {
        parent = current;
        if (strcmp(line, parent->word) < 0) //比root小 往左子樹繼續搜尋
        {
            current = parent->l_child; //繼續比對
            if (current == NULL)       // insert
            {
                parent->l_child = tmp; //接起來
                break;
            }
        }
        else //比root大  往右子樹繼續搜尋
        {
            current = parent->r_child; //繼續比對
            if (current == NULL)       // insert
            {
                parent->r_child = tmp; //接起來
                break;
            }
        }
    }
    return root;
}

void inOrderTraversal(struct Tnode *root)
{
    if (root != NULL)
    {
        inOrderTraversal(root->l_child);
        printf("%d %s", root->cnt, root->word);
        inOrderTraversal(root->r_child);
    }
}

int tree2Array(struct Tnode *root, struct Tnode *arr, int i)
{
    // in order traversal的方式轉成array i控制array的top
    if (root == NULL)
        return i;
    if (root->l_child != NULL)
        i = tree2Array(root->l_child, arr, i);
    strcpy(arr[i].word, root->word);
    arr[i].cnt = root->cnt;
    i++;
    if (root->r_child != NULL)
        i = tree2Array(root->r_child, arr, i);
    free(root);
    return i; //回傳array的top
}

void bubble(struct Tnode *arr, int cnt)
{
    //按照cnt大小排序 array內的資料是in order traversal的順序
    struct Tnode tmp;
    for (int i = 0; i < cnt; i++)
    {
        for (int j = 0; j < cnt - i - 1; j++)
        {
            if (arr[j].cnt < arr[j + 1].cnt)
            {
                tmp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = tmp;
            }
        }
    }
    for (int i = 0; i < cnt; i++)
    {
        printf("%d %s", arr[i].cnt, arr[i].word);
    }
    // printf("\n");
}

/*void freeTree(struct Tnode *root)
{
    if(root == NULL)    return;
    if(root->l_child != NULL)   freeTree(root->l_child);
    if(root->r_child != NULL)   freeTree(root->r_child);
    free(root);
}*/

int main()
{
    char line[Max];
    struct Tnode *root = NULL; //一開始就malloc 在insert函式中判斷是第一個會有問題
    struct Tnode *ret = NULL;
    struct Tnode arr[1024];
    int cnt = 0;
    while (fgets(line, Max, stdin) != NULL)
    {
        if (strlen(line) <= 1)
            continue; //跳過空行

        if (line[0] == '-')
            ret = BSTfind(root, line + 1); //先找 有減號的話從減號後開始找
        else
            ret = BSTfind(root, line); //找

        if (ret != NULL) //有找到
        {
            // printf("find!\n");
            if (line[0] == '-')
                ret->cnt--; //有減號 cnt--
            else
                ret->cnt++; //無減號 cnt++
        }
        else //沒找到
        {
            // printf("not found!\n");
            root = insert(root, line); //沒找到 要insert
        }
    }
    printf("Inorder traversal:\n");
    inOrderTraversal(root); //印出tree的data跟cnt
    printf("\n");
    printf("Count sorting:\n");
    cnt = tree2Array(root, arr, cnt); //把資料轉成array 回傳array的top
    bubble(arr, cnt);                 // sort and print
    // freeTree(root);
    return 0;
}