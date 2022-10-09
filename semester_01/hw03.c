#include <stdio.h>

int main()
{
    int i, n, k;
    int maxScore, minScore;
    int score[100];
    float sum, avgScore;
    scanf("%d", &n);
    for (i = 0; i < n; i++)
    {
        scanf("%d", &score[i]);
    }

    // let score from min to max
    for (k = 0; k < n - k; k++)
    {
        for (i = 0; i < n - 1; i++)
        {
            if (score[i] > score[i + 1])
            {
                int tmp;
                tmp = score[i + 1];
                score[i + 1] = score[i];
                score[i] = tmp;
            }
        }
    }

    // find maxScore
    maxScore = score[n - 1];
    printf("maxScore=%d\n", maxScore);

    // find minScore
    minScore = score[0];
    printf("minScore=%d\n", minScore);

    // compute avgScore
    sum = 0;
    for (i = 0; i < n; i++)
    {
        sum += score[i];
    }
    avgScore = sum / n;
    printf("avgScore=%.2f\n", avgScore);

    // print from Min to Max
    printf("Min to Max=");
    for (i = 0; i < n; i++)
    {
        printf("%d ", score[i]);
    }
    printf("\n");

    // print from Max to Min
    printf("Max to Min=");
    for (i = n - 1; i >= 0; i--)
    {
        printf("%d ", score[i]);
    }
    printf("\n");

    return 0;
}