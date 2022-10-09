#include <stdio.h>

int main()
{
    int row, colspace, colstar, q;
    while (scanf("%d", &q) != EOF)
    {
        if (q % 2 != 0)
        { //找出印出幾行 並印出上半部
            q = q;
        }
        else
        {
            q = q - 1;
        }
        for (row = 1; row <= (q / 2) + 1; row++)
        { //印出上半部
            for (colspace = (q / 2) + 1 - row; colspace >= 1; colspace--)
            {
                printf(" ");
            }
            for (colstar = 1; colstar <= 2 * row - 1; colstar++)
            {
                printf("*");
            }
            printf("\n");
        }

        for (row = q / 2; row >= 1; row--)
        { //印出下半部
            for (colspace = 1; colspace <= q / 2 - row + 1; colspace++)
            {
                printf(" ");
            }
            for (colstar = 1; colstar <= 2 * row - 1; colstar++)
            {
                printf("*");
            }
            printf("\n");
        }
    }
    return 0;
}