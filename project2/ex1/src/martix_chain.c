#include <stdio.h>
#include <malloc.h>
#include <limits.h>
#define MAX_LENGTH 100
void martix_chain_order(int *array, int length);
void print_optimal_parens(int i, int j);
int ReadData();
int input[MAX_LENGTH];
long long m[MAX_LENGTH][MAX_LENGTH];
int s[MAX_LENGTH][MAX_LENGTH];
FILE *in;
int main()
{
    FILE *out;
    int leng;
    printf("This is the program to solve martix chain order.\n");
    in = fopen("../input/2_1_input.txt", "r");
    while (in != EOF)
    {
        leng = ReadData(in);
        martix_chain_order(input, leng);
        printf("\n");
        /*for (int i = 1; i <= leng; i++)
        {
            for (int j = 1; j <= leng; j++)
            {
                printf("%d ", s[i][j]);
            }
            printf("\n");
        }*/
        print_optimal_parens(1, leng);
    }
}

int ReadData()
{
    int n;
    int i;
    fscanf(in, "%d\n", &n);
    for (i = 0; i < n; i++)
        fscanf(in, "%d", &input[i]);
    fscanf(in, "%d\n", &input[i]);
    for (i = 0; i <= n; i++)
        printf("%d ", input[i]);
    return n;
}

void martix_chain_order(int *array, int length)
{
    int n = length;

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
        printf("A%d", i);
    else
    {
        printf("(");
        print_optimal_parens(i, s[i][j]);
        print_optimal_parens(s[i][j] + 1, j);
        printf(")");
    }
}