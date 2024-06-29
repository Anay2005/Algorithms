#include <stdio.h>


typedef struct index_value_pair
{
    int value;
    int index
} index_value_pair;


int main(void)
{
    int prices[] = {7,1,5,3,6,4};
    size_t pricesSize = sizeof(prices) / sizeof(prices[0]);
    // make an array of index and value pairs
    index_value_pair prices_pair[pricesSize];
    for(size_t i = 0; i < pricesSize; i++)
    {
        prices_pair[i].index = i;
        prices_pair[i].value = prices[i];
    }

    int max_profit = maxProfit(prices, pricesSize);
    printf("Max profit: %d\n", max_profit);
    return 0;
}
int maxProfit(int* prices, int pricesSize) 
{


}

