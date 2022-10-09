#include <stdio.h>

float CalculateBMI(float Height, float Weight)
{
    float bmi;
    bmi = Weight / ((Height / 100) * (Height / 100));
    return bmi;
}

int main(void)
{
    float height, weight;
    float BMI;
    while (scanf("%f %f", &height, &weight) != EOF)
    {
        if ((height <= 200 && height > 0) && (weight <= 200 && weight > 0))
        {
            BMI = CalculateBMI(height, weight);
            printf("BMI is %.1f\n", BMI);
        }
        else
        {
            printf("Please enter again!\n");
        }
    }
    return 0;
}
