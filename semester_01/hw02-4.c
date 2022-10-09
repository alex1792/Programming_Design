#include <stdio.h>
#include <string.h>
int main()
{
    char input[101];
    while (scanf("%s", input) != EOF)
    {
        int i;
        for (i = 0; i < strlen(input); i++)
        {
            input[i] -= 5;
        }
        printf("%s\n", input);
    }
    return 0;
}