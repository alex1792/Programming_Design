#include <stdio.h>
int main()
{
    int n;
    while (scanf("%d", &n) != EOF)
    {
        if (n >= 1900 && n <= 2099)
            if ((n % 4 == 0 && n % 100 != 0) || (n % 400 == 0 && n % 3200 != 0))
                printf("Leap year!\n");
            else
                printf("Common year!\n");
        else
            printf("The year number must between 1900 and 2099.\n");
    }
    return 0;
}