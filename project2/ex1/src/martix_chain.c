#include <stdio.h>
#include <malloc.h>
#include <limits.h>
#define MAX_LENGTH 100
void martix_chain_order(int *array, int length);
void print_optimal_parens(int i, int j);
int ReadData(FILE *f);
int input[MAX_LENGTH];
long long m[MAX_LENGTH][MAX_LENGTH];
int s[MAX_LENGTH][MAX_LENGTH];
int main()
{
    FILE *in, *out;
    int leng;
    printf("This is the program to solve martix chain order.\n");
    in = fopen("../input/2_1_input.txt", "r");
    while (in!=EOF)
    {
        leng=ReadData(in);
        martix_chain_order(input,leng);
        print_optimal_parens(1,leng);
    }
    
}

int ReadData(FILE *f)
{
    int n;
    int i;
    fscanf("%d\n",&n);
    for(i=0;i<n-1;i++){
        fscanf("%d ",&input[i]);
    }
    fscanf("%d\n",&input[i]);
    return n;
}

void martix_chain_order(int *array, int length)
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
        printf("A%d", i);
    else
    {
        printf("(");
        print_optimal_parens(i, s[i, j]);
        print_optimal_parens(s[i, j] + 1, j);
        printf(")");
    }
}