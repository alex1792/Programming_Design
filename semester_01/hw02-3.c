#include <stdio.h>

int GetCycleLength(int n)
{
    int cyclelength = 1;
    while (n > 1)
    {
        if (n % 2 == 0)
        {
            n = n / 2;
        }
        else
        {
            n = 3 * n + 1;
        }
        cyclelength++;
    }
    return cyclelength;
}

int main()
{
    int input1, input2;
    int top, bottom;
    int i, max, cycle_length;
    while ((scanf("%d %d", &input1, &input2) != EOF) && (input1 >= 0 && input2 >= 0))
    {
        if (input1 > input2)
        {
            bottom = input2;
            top = input1;
        }
        else if (input1 == 0 && input2 == 0)
        {
            break;
        }
        else
        {
            bottom = input1;
            top = input2;
        }
        max = 0;
        for (i = bottom; i <= top; i++)
        {
            cycle_length = GetCycleLength(i);
            if (cycle_length > max)
            {
                max = cycle_length;
            }
        }
        printf("%d %d %d\n", input1, input2, max);
    }
    return 0;
}