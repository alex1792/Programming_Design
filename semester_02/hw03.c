#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#define Max 1025

void rmSpace(char *line, char *newLine)
{
    char *ptr = line;
    char *qtr = newLine;
    newLine[0] = 0;
    ptr += 2;
    while (*ptr != '\0')
    {
        if (*ptr != ' ')
        {
            *qtr++ = *ptr++;
        }
        else
        {
            ptr++;
        }
    }
    *qtr = '\0';
}

void addSpace(char *string, int *cnt)
{
    string[*cnt] = ' ';
    *cnt += 1;
}

void Push2Stack(char *stack, int *top, char ptr)
{
    *top += 1;
    stack[*top] = ptr;
}

void Push2String(char *string, int *cnt, char ptr)
{
    string[*cnt] = ptr;
    *cnt += 1;
}

void pop(char *stack, int *top, char *string, int *cnt)
{
    string[*cnt] = stack[*top];
    stack[*top] = 0;
    *cnt += 1;
    *top -= 1;
}

int isOperand(char ch)
{
    if (ch <= '9' && ch >= '0')
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

int isOperator(char ch)
{
    if (ch == '+' || ch == '-' || ch == '*' || ch == '/')
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

int priority(char operator)
{
    if (operator== '+' || operator== '-')
    {
        return 1;
    }
    else if (operator== '*' || operator== '/')
    {
        return 2;
    }
    else
    {
        return 0;
    }
}

void infix2postfix(char *line)
{
    char stack[Max];
    char string[Max];
    char *ptr = NULL;
    int cnt = 0;
    int top = 0;
    stack[0] = '\0';
    stack[top] = '?';
    string[0] = '\0';
    ptr = line;
    while (*ptr != '\n')
    {
        if (isOperand(*ptr)) //是數字
        {
            Push2String(string, &cnt, *ptr);
        }
        else if (*ptr == '(')
        {
            Push2Stack(stack, &top, *ptr);
        }
        else if (*ptr == ')')
        {
            while (stack[top] != '(') //先把括號內的符號pop出來
            {
                addSpace(string, &cnt);
                pop(stack, &top, string, &cnt);
            }
            stack[top] = 0;
            top--; //  跳過'('
        }
        else // operator
        {
            // string[cnt] = ' ';
            // cnt++;
            if (priority(*ptr) > priority(stack[top]))
            {
                Push2Stack(stack, &top, *ptr);
                addSpace(string, &cnt);
            }
            else
            {
                while (priority(*ptr) <= priority(stack[top]))
                { //把priority比當前高的pop出去
                    addSpace(string, &cnt);
                    pop(stack, &top, string, &cnt);
                }
                Push2Stack(stack, &top, *ptr); //把當前的push回stack
                addSpace(string, &cnt);
            }
        }
        ptr++;
    }
    while (stack[top] != '?' && top > 0)
    { //結束後全部pop出來
        addSpace(string, &cnt);
        pop(stack, &top, string, &cnt);
    }
    addSpace(string, &cnt);
    string[cnt] = '\n';
    string[cnt + 1] = '\0';
    printf("%s", string);
    stack[0] = '\0';
    string[0] = '\0';
    top = 0;
}

void postfix(char *line)
{
    long long stack[Max];
    int top = -1;
    char *ptr = line;
    char data[Max];
    char *qtr = data;
    stack[0] = 0;
    ptr += 3;
    while (*ptr != '\n')
    {
        data[0] = 0;
        qtr = data;
        while (*ptr != ' ' && *ptr != '\0')
        {
            *qtr++ = *ptr++;
        }
        *qtr = 0;
        ptr++;
        if (atoi(data) != 0)
        {
            top++;
            stack[top] = atoi(data);
        }
        else
        {
            if (data[0] == '+')
            {
                stack[top - 1] = stack[top - 1] + stack[top];
                top--;
            }
            else if (data[0] == '-')
            {
                stack[top - 1] = stack[top - 1] - stack[top];
                top--;
            }
            else if (data[0] == '*')
            {
                stack[top - 1] = stack[top - 1] * stack[top];
                top--;
            }
            else if (data[0] == '/')
            {
                stack[top - 1] = stack[top - 1] / stack[top];
                top--;
            }
        }
    }
    printf("%lld\n", stack[top]);
}

int main()
{
    char line[Max], newLine[Max];
    newLine[0] = 0;
    while (fgets(line, Max, stdin) != NULL)
    {
        if (line[0] == 'i')
        {
            rmSpace(line, newLine);
            infix2postfix(newLine);
        }
        else if (line[0] == 'p')
        {
            postfix(line);
        }
        line[0] = '\0';
        newLine[0] = '\0';
    }
    return 0;
}