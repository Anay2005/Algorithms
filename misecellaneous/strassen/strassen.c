#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void add(int n, int a[n][n], int b[n][n], int c[n][n]) 
{
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            c[i][j] = a[i][j] + b[i][j];
}

// implementation of partititon
void partition(int n, int original_matrix[n][n], int a[n / 2][n / 2], int b[n / 2][n / 2], int c[n / 2][n / 2], int d[n / 2][n / 2])
{
    // iterate over the original matrix
    for (int row = 0; row < n; row++)
    {
        for (int col = 0; col < n; col++)
        {
            // conditions to detect boundary from where to cut the array.
            if (row < n / 2 && col < n / 2)
            {
                // top left half goes into a
                a[row][col] = original_matrix[row][col];
            }
            else if (row < n / 2 && col >= n / 2)
            {
                // top right half goes into b
                b[row][col - n / 2] = original_matrix[row][col];
            }
            else if (row >= n / 2 && col < n / 2)
            {
                // bottom left half goes into c
                c[row - n / 2][col] = original_matrix[row][col];
            }
            else
            {
                // bottom right half goes into d
                d[row - n / 2][col - n / 2] = original_matrix[row][col];
            }
        }
    }
    return;
}
// implementation of fill
void fill(int n, int a[n][n], int b[n][n])
{
    // iterate over a and b
    for (int row = 0; row < n; row++)
    {
        for (int col = 0; col < n; col++)
        {
            // fill 'a' from numbers ranging from 0 to 10
            a[row][col] = rand() % 10;
            // fill 'b' from numbers ranging from 0 to 10
            b[row][col] = rand() % 10;
        }
    }
    return;
}
// impelementation of multiply
void multiply(int n, int a[n][n], int b[n][n], int c[n][n])
{
    // base case
    if (n <= 2)
    {
        // for a 2x2 matrix perform strassen caluclations
        int p = (a[0][0] + a[1][1]) * (b[0][0] + b[1][1]);
        int q = (a[1][0] + a[1][1]) * b[0][0];
        int r = a[0][0] * (b[0][1] - b[1][1]);
        int s = a[1][1] * (b[1][0] - b[0][0]);
        int t = (a[0][0] + a[0][1]) * b[1][1];
        int u = (a[1][0] - a[0][0]) * (b[0][0] + b[0][1]);
        int v = (a[0][1] - a[1][1]) * (b[1][0] + b[1][1]);
        // fill the resultant 2x2 matrix
        c[0][0] = p + s - t + v;
        c[0][1] = r + t;
        c[1][0] = q + s;
        c[1][1] = p + r - q + u;
        
        return;
    }
    // declare arrays to hold the partitioned matrix for a,b and c
    int a11[n / 2][n / 2], a12[n / 2][n / 2], a21[n / 2][n / 2], a22[n / 2][n / 2];
    int b11[n / 2][n / 2], b12[n / 2][n / 2], b21[n / 2][n / 2], b22[n / 2][n / 2];
    int c11[n / 2][n / 2], c12[n / 2][n / 2], c21[n / 2][n / 2], c22[n / 2][n / 2];
    int temp[n/2][n/2], temp2[n/2][n/2];

    // intialize c's partition matrix to 0 as it holds the result of multiplication
    for (int row = 0; row < n / 2; row++)
    {
        for (int col = 0; col < n / 2; col++)
        {
            c11[row][col] = 0;
            c12[row][col] = 0;
            c21[row][col] = 0;
            c22[row][col] = 0;
        }
    }
    // partition 'a' matrix into 4 equal parts
    partition(n, a, a11, a12, a21, a22);
    // partition 'b' matrix into 4 equal parts
    partition(n, b, b11, b12, b21, b22);
    // partition 'c' matrix into 4 equal parts
    partition(n, c, c11, c12, c21, c22);
    // there are 8 matrices to multiply after partitioning
    multiply(n / 2, a11, b11, temp);
    multiply(n / 2, a12, b21, temp2);
    add(n/2, temp, temp2, c11);

    multiply(n / 2, a11, b12, temp);
    multiply(n / 2, a12, b22, temp2);
    add(n/2, temp, temp2, c12);

    multiply(n / 2, a21, b11, temp);
    multiply(n / 2, a22, b21, temp2);
    add(n/2, temp, temp2, c21);

    multiply(n / 2, a21, b12, temp);
    multiply(n / 2, a22, b22, temp2);
    add(n/2, temp, temp2, c22);
    // transfer the result of the partitions back to 'c'
    for (int row = 0; row < n / 2; row++)
    {
        for (int col = 0; col < n / 2; col++)
        {
            c[row][col] = c11[row][col];
            c[row][col + n / 2] = c12[row][col];
            c[row + n / 2][col] = c21[row][col];
            c[row + n / 2][col + n / 2] = c22[row][col];
        }
    }
    return;
}
// driver function
int main(void)
{
    // seed time generator
    srand(time(NULL));
    // ask for user input of n where n is a power of 2
    int n;
    printf("Enter an integer: ");
    scanf("%d", &n);
    // declare arrays for multiplication
    int A[n][n];
    int B[n][n];
    // declare array to hold the result
    int C[n][n];
    // intialize C to 0 as it holds the result
    for (int row = 0; row < n; row++)
    {
        for (int col = 0; col < n; col++)
        {
            C[row][col] = 0;
        }
    }
    // randomly fill A and B
    fill(n, A, B);
    // print to check if 'A' is correctly filled
    for (int row = 0; row < n; row++)
    {
        for (int col = 0; col < n; col++)
        {
            printf("%d ", A[row][col]);
        }
        printf("\n");
    }
    printf("\n\n");
    // print to check if 'B' is correctly filled
    for (int row = 0; row < n; row++)
    {
        for (int col = 0; col < n; col++)
        {
            printf("%d ", B[row][col]);
        }
        printf("\n");
    }
    printf("\n");
    // multiply A and B
    multiply(n, A, B, C);
    // print to check if multiplication is correct
    for (int row = 0; row < n; row++)
    {
        for (int col = 0; col < n; col++)
        {
            printf("%d ", C[row][col]);
        }
        printf("\n");
    }
    return 0;
}