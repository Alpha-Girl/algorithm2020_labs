#include <stdio.h>
#include <malloc.h>
#include <limits.h>
#define MAX_LENGTH 100
void martix_chain_order(long long *array, int length);
void print_optimal_parens(int i, int j);
long long m[MAX_LENGTH][MAX_LENGTH];
int s[MAX_LENGTH][MAX_LENGTH];
int main()
{
}

void martix_chain_order(long long *array, int length)
{
    int n = length - 1;

    int i, j, k, l;
    long long tmp;
    for (i = 1; i <= n; i++)
    {
        m[i][i] = 0;
    }
    for (l = 2; l <= n; l++)
    {
        for (i = 1; i <= n - l + 1; i++)
        {
            j = i + l - 1;
            m[i][j] = LLONG_MAX;
            for (k = i; k <= j - 1; k++)
            {
                tmp = m[i][k] + m[k + 1][j] + array[i - 1] * array[i] * array[i + 1];
                if (tmp < m[i][j])
                {
                    m[i][j] = tmp;
                    s[i][j] = k;
                }
            }
        }
    }
}

void print_optimal_parens(int i, int j)
{
    if (i == j)
        printf("A");
    else
    {
        printf("(");
        print_optimal_parens(i, s[i, j]);
        print_optimal_parens(s[i, j] + 1, j);
        printf(")");
    }
}