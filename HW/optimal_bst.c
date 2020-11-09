#include <stdio.h>

int main()
{
    float e[9][9];
    float w[9][9];
    int root[9][9];
    int i, j, l;
    float t;
    float p[8] = {0, 0.04, 0.03, 0.08, 0.02, 0.10, 0.12, 0.14};
    float q[8] = {0.06, 0.06, 0.06, 0.06, 0.05, 0.05, 0.05, 0.05};
    int n = 7;
    for (i = 0; i <= n + 1; i++)
    {
        for (j = 0; j <= n + 1; j++)
        {
            e[i][j] = 0.0;
            w[i][j] = 0.0;
            root[i][j] = 0;
        }
    }
    for (i = 1; i <= n + 1; i++)
    {
        e[i][i - 1] = q[i - 1];
        w[i][i - 1] = q[i - 1];
    }
    for (l = 1; l <= n; l++)
    {
        for (i = 1; i <= n - l + 1; i++)
        {
            j = i + l - 1;
            e[i][j] = 100;
            w[i][j] = w[i][j - 1] + p[j] + q[j];
            for (int r = i; r <= j; r++)
            {
                t = e[i][r - 1] + e[r + 1][j] + w[i][j];
                if (t < e[i][j])
                {
                    e[i][j] = t;
                    root[i][j] = r;
                }
            }
        }
    }
    printf("e\n");
    for (i = 1; i <= n + 1; i++)
    {
        for (j = 0; j <= n; j++)
        {
            printf("%.2f ", e[i][j]);
        }
        printf("\n");
    }
    printf("w\n");
    for (i = 1; i <= n + 1; i++)
    {
        for (j = 0; j <= n; j++)
        {
            printf("%.2f ", w[i][j]);
        }
        printf("\n");
    }
    printf("r\n");
    for (i = 1; i <= n; i++)
    {
        for (j = 1; j <= n; j++)
        {
            printf("%d ", root[i][j]);
        }
        printf("\n");
    }
}