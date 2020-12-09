#include <stdio.h>
#include <malloc.h>
#include <windows.h>
#include "complex.h"

#define MAX_LENGTH 300

complex arr[MAX_LENGTH]; //输入
complex res[MAX_LENGTH]; //输出

FILE *in, *out, *time; //输入文件，输出文件，计时结果文件

double t[MAX_LENGTH]; //计时结果数组

void recursive_fft(complex *array, complex *result, int length);
int ReadData();

int main()
{
    //打开文件
    in = fopen("../input/2_2_input.txt", "r");
    out = fopen("../output/result.txt", "w");
    time = fopen("../output/time.txt", "w");

    double run_time;
    LARGE_INTEGER time_start; //开始时间
    LARGE_INTEGER time_over;  //结束时间
    double dqFreq;            //计时器频率
    LARGE_INTEGER f;          //计时器频率
    QueryPerformanceFrequency(&f);
    dqFreq = (double)f.QuadPart;

    int flag = 1, leng, j = 0, i;

    while (!feof(in))
    {
        //读取一组输入
        leng = ReadData();
        printf("\nsize of input: %d\n", leng);

        QueryPerformanceCounter(&time_start); //计时开始
        recursive_fft(arr, res, leng);
        QueryPerformanceCounter(&time_over); //计时结束
        run_time = 1000000 * (time_over.QuadPart - time_start.QuadPart) / dqFreq;
        t[j] = run_time;
        j++;

        //输出2^3的结果
        if (flag)
        {
            printf("\n result of 2^3:\n");
            for (i = 0; i < leng; i++)
                printf(" %f ", res[i].Re);
            printf("\n");
            flag = 0;
        }
        for (i = 0; i < leng; i++)
            fprintf(out, " %f ", res[i].Re);
        fprintf(out, "\n");
        fprintf(time, "%lf\n", t[j - 1]);
    }
    fclose(in);
    fclose(out);
    fclose(time);
}

void recursive_fft(complex *array, complex *result, int length)
{
    int n = length;
    if (n == 1)
    {
        equal(array, result);
        return;
    }
    complex omiga_n, tmp;
    exp_i(2 / (float)n, &omiga_n);
    complex omiga = {1, 0};
    complex *a_0, *a_1, *y_0, *y_1;
    a_0 = (complex *)calloc(n / 2, sizeof(complex));
    a_1 = (complex *)calloc(n / 2, sizeof(complex));
    y_0 = (complex *)calloc(n / 2, sizeof(complex));
    y_1 = (complex *)calloc(n / 2, sizeof(complex));
    for (int i = 0; i < n / 2; i++)
    {
        equal(&array[2 * i], &a_0[i]);
        equal(&array[2 * i + 1], &a_1[i]);
    }
    recursive_fft(a_0, y_0, n / 2);
    recursive_fft(a_1, y_1, n / 2);
    for (int k = 0; k < n / 2; k++)
    {
        multiply(&omiga, &y_1[k], &tmp);
        plus(&y_0[k], &tmp, &result[k]);
        miuns(&y_0[k], &tmp, &result[k + n / 2]);
        multiply(&omiga_n, &omiga, &tmp);
        equal(&tmp, &omiga);
        //printf("\n %f + %fi %f + %fi", result[k].Re, result[k].Im, result[k + n / 2].Re, result[k + n / 2].Im);
        //printf("\n %f + %fi %f + %fi", res[k].Re, res[k].Im, res[k + n / 2].Re, res[k + n / 2].Im);
    }
    free(a_0);
    free(a_1);
    free(y_0);
    free(y_1);
    return;
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
    for (i = 0; i < n - 1; i++)
        fscanf(in, "%f", &arr[i].Re);
    fscanf(in, "%f\n", &arr[i].Re);
    /*for (i = 0; i <= n; i++)
        printf("%d ", input[i]);*/
    return n;
}
