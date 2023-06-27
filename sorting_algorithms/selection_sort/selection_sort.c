
#include <stdio.h>

int main(void)
{
    int votes[4] = {4, 7, 3, 8};
    int a;
    for (int i = 0; i < 4; i++)
    {
        for (int j = i + 1; j < 4; j++)
        {
            if (votes[i] < votes[j])
            {
                a = votes[i];
                votes[i] = votes[j];
                votes[j] = a;
            }
        }
    }
    for (int l = 0; l < 4; l++)
    {
        printf("%i", votes[l]);
    }
}
