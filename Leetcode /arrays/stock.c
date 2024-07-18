/*
    * Problem: Best Time to Buy and Sell Stock
    * Say you have an array for which the ith element is the price of a given stock on day i.
    * If you were only permitted to complete at most one transaction 
    * (i.e., buy one and sell one share of the stock), design an algorithm to find the maximum profit.
    * Note that you cannot sell a stock before you buy one.
    * Example 1:
    * Input: [7, 1, 5, 3, 6, 4]
    * Output: 5
    * Explanation: Buy on day 2 (price = 1) and sell on day 5 (price = 6), profit = 6-1 = 5.
    * Not 7-1 = 6, as selling price needs to be larger than buying price.
    * Example 2:
    * Input: [7, 6, 4, 3, 1]
    * Output: 0
    * Explanation: In this case, no transaction is done, i.e. max profit = 0.
    time complexity: O(n) optimized solution
*/

#include <stdio.h>


int maxProfit(int *prices, int pricesSize);
int main(void)
{
    int prices[] = {7, 1, 5, 3, 6, 4};
    size_t pricesSize = sizeof(prices) / sizeof(prices[0]);
    
    int max_profit = maxProfit(prices, pricesSize);
    printf("Max profit: %d\n", max_profit);
    return 0;
}
int maxProfit(int *prices, int pricesSize)
{
    // No profit can be made with less than 2 prices
    if (pricesSize < 2)
        return 0; 
    // start with the first price as the minimum
    int min_price = prices[0];
    // No profit at the start
    int max_profit = 0;
    // search for the minimum price and the maximum profit
    for (int i = 1; i < pricesSize; i++)
    {
        // set the minimum price for each iteration
        if (prices[i] < min_price)
        {
            min_price = prices[i];
        }
        else
        {
            // calculate the profit
            int profit = prices[i] - min_price;
            // update the maximum profit
            if (profit > max_profit)
            {
                max_profit = profit;
            }
        }
    }

    return max_profit;
}
