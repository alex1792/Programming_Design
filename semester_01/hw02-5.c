#include <stdio.h>
#include <string.h>

int main()
{
    char input[11];
    while (scanf("%s", input) != EOF)
    {
        int i;
        for (i = strlen(input) - 1; i >= 0; i--)
        {
            printf("%c", input[i]);
        }
        printf("\n");
    }
    return 0;
}