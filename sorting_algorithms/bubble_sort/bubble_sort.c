#include <stdio.h>

int main(void)
{
    int votes[4] = {2, 9, 8, 5};
    int swap_counter = 0;
    int a;
    for (int i = 0; i < 4; i++)
    {
        swap_counter = 0;
        for (int j = 0; j < 3; j++)
        {
            if (votes[j + 1] < votes[j])
            {
                a = votes[j];
                votes[j] = votes[j + 1];
                votes[j + 1] = a;
                swap_counter++;
            }
        }
        if (swap_counter == 0)
        {
            break;
        }
    }
    for (int l = 0; l < 4; l++)
    {
        printf("%i", votes[l]);
    }
    printf("\n");
}
