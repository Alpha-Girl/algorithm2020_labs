/*********** 
文件名：martix_chain.c 
作者：胡毅翔 
学号：PB18000290 
文件主要功能：读取input.txt中的矩阵规模，并输出矩阵链乘最优方案。 
************/
#include <stdio.h>
#include <malloc.h>
#include <limits.h>
#include <windows.h>
#define MAX_LENGTH 100

void martix_chain_order(int *array, int length);
void print_optimal_parens(int i, int j);
int ReadData();

int input[MAX_LENGTH];
long long m[MAX_LENGTH][MAX_LENGTH];
int s[MAX_LENGTH][MAX_LENGTH];
double t[MAX_LENGTH];

FILE *in, *out;

int main()
{
    FILE *time;
    int leng, i = 0, j = 0;
    printf("This is the program to solve martix chain order.\n");
    long long a = 1;
    printf("%lld\n", a);
    in = fopen("../input/2_1_input.txt", "r");
    out = fopen("../output/result.txt", "w");
    time = fopen("../output/time.txt", "w");

    double run_time;
    LARGE_INTEGER time_start; //开始时间
    LARGE_INTEGER time_over;  //结束时间
    double dqFreq;            //计时器频率
    LARGE_INTEGER f;          //计时器频率
    QueryPerformanceFrequency(&f);
    dqFreq = (double)f.QuadPart;

    while (!feof(in))
    {
        leng = ReadData(in);
        printf("\nsize of input: %d\n", leng);

        QueryPerformanceCounter(&time_start); //计时开始
        martix_chain_order(input, leng);
        QueryPerformanceCounter(&time_over); //计时结束
        run_time = 1000000 * (time_over.QuadPart - time_start.QuadPart) / dqFreq;
        t[j] = run_time;
        j++;

        printf("\n array of s[][]:\n");
        for (i = 1; i <= leng; i++)
        {
            for (int j = 1; j <= leng; j++)
                printf("%2d", s[i][j]);
            printf("\n");
        }

        printf("\n array of m[][]:\n");
        for (int i = 1; i <= leng; i++)
        {
            for (int j = 1; j <= leng; j++)
                printf("%lld ", m[i][j]);
            printf("\n");
        }
        print_optimal_parens(1, leng);
        fprintf(out, "%lld\n", m[leng][leng]);
    }
    for (i = 0; i < j; i++)
        fprintf(time, "%lf\n", t[i]);
    fclose(in);
    fclose(out);
    fclose(time);
    printf("finished");
    system("PAUSE");
}

/*********** 
函数名：ReadData 
函数功能描述：从input.txt中读取一组输入 
输入参数的类型和意义：无 
输出参数的类型和意义：无 
************/
int ReadData()
{
    int n;
    int i;
    fscanf(in, "%d\n", &n);
    for (i = 0; i < n; i++)
        fscanf(in, "%d", &input[i]);
    fscanf(in, "%d\n", &input[i]);
    /*for (i = 0; i <= n; i++)
        printf("%d ", input[i]);*/
    return n;
}

/*********** 
函数名：martix_chain_order 
函数功能描述：传入矩阵规模数组及矩阵链长度，
将过程中得到的方案(划分位置及对应的乘法次数)保存到全局数组s[][]和m[][]中
输入参数的类型和意义：矩阵规模数组(int *)及矩阵链长度(int) 
输出参数的类型和意义：无 
************/
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
                tmp = m[i][k] + m[k + 1][j] + (long long)(array[i - 1] * array[i] * array[i + 1]);
                if (tmp < m[i][j])
                {
                    m[i][j] = tmp;
                    s[i][j] = k;
                }
            }
        }
    }
}

/*********** 
函数名：print_optimal_parens 
函数功能描述：输出第i至第j个矩阵间的最优方案
输入参数的类型和意义：起始，终止矩阵序号(int) 
输出参数的类型和意义：无 
************/
void print_optimal_parens(int i, int j)
{
    if (i == j)
    {
        printf("A%d", i);
        fprintf(out, "A%d", i);
    }
    else
    {
        printf("(");
        fprintf(out, "(");
        print_optimal_parens(i, s[i][j]);
        print_optimal_parens(s[i][j] + 1, j);
        printf(")");
        fprintf(out, ")");
    }
}