#include <windows.h>
#include "sort.h"
int in[262144];
int CopyAndCheck(int *a, int *b, int n);

int main()
{
    FILE *f_in, *f_out, *f_time;
    int n, *array, *save, *result, k, *t;
    double tt[6];
    int begintime, endtime;
    long size;
    int start, end;
    //print README
    printf("***README***\n");
    printf("----------------------------------------------------------------\n");
    printf("The sort.exe will 'k' arraies, of which size are 'n' of 2,\n");
    printf("using InsertionSort,QuickSort,HeapSort,MergeSort,andCountingSort.\n");
    printf("Then it will output the average time of each algorithm.\n");
    printf("----------------------------------------------------------------\n");
    //get parameter
    printf("----------------------------------------------------------------\n");
    printf("Starting...\n");
    //init
    printf("1.Generate random numbers, store in input.txt.\n");
    size = pow(2, 18);
    f_in = fopen("../input/input.txt", "w");
    if (f_in == NULL)
        printf("Fail to open input.txt.\n");

    double run_time;
    LARGE_INTEGER time_start; //开始时间
    LARGE_INTEGER time_over;  //结束时间
    double dqFreq;            //计时器频率
    LARGE_INTEGER f;          //计时器频率
    QueryPerformanceFrequency(&f);
    dqFreq = (double)f.QuadPart;
    QueryPerformanceCounter(&time_start); //计时开始

    QueryPerformanceCounter(&time_over); //计时结束
    run_time = 1000000 * (time_over.QuadPart - time_start.QuadPart) / dqFreq;
    //乘以1000000把单位由秒化为微秒，精度为1000 000/（cpu主频）微秒

    srand(time(NULL));

    for (int i = 0; i < size; i++)
    {
        in[i] = rand();
        fprintf(f_in, "%d\n", in[i]);
    }
    fclose(f_in);
    printf("Finished 1.\n");
    //Insertion Sort
    printf("size 2^3,start\n");
    size = pow(2, 3);
    QueryPerformanceCounter(&time_start);
    InsertionSort(in, size);
 QueryPerformanceCounter(&time_over); 
    f_out = fopen("../output/insertion_sort/result_3.txt", "w");
    for (int i = 0; i < size; i++)
    {
        fprintf(f_out, "%d\n", in[i]);
    }
    fclose(f_out);
    tt[0] = 1000000 * (time_over.QuadPart - time_start.QuadPart) / dqFreq;
    printf("size 2^3,end\n");

    printf("size 2^6,start\n");
    size = pow(2, 6);
    f_in = fopen("../input/input.txt", "r");
    for (int i = 0; i < size; i++)
        fscanf(f_in, "%d\n", &in[i]);
    fclose(f_in);
    QueryPerformanceCounter(&time_start);
    InsertionSort(in, size);
 QueryPerformanceCounter(&time_over); 
    f_out = fopen("../output/insertion_sort/result_6.txt", "w");
    for (int i = 0; i < size; i++)
    {
        fprintf(f_out, "%d\n", in[i]);
    }
    fclose(f_out);
    tt[1] = 1000000 * (time_over.QuadPart - time_start.QuadPart) / dqFreq;
    printf("size 2^6,end\n");

    printf("size 2^9,start\n");
    size = pow(2, 9);
    f_in = fopen("../input/input.txt", "r");
    for (int i = 0; i < size; i++)
        fscanf(f_in, "%d\n", &in[i]);
    fclose(f_in);
  QueryPerformanceCounter(&time_start);
    InsertionSort(in, size);
 QueryPerformanceCounter(&time_over); 
    f_out = fopen("../output/insertion_sort/result_9.txt", "w");
    for (int i = 0; i < size; i++)
    {
        fprintf(f_out, "%d\n", in[i]);
    }
    fclose(f_out);
    tt[2] = 1000000 * (time_over.QuadPart - time_start.QuadPart) / dqFreq;
    printf("size 2^9,end\n");

    printf("size 2^12,start\n");
    size = pow(2, 12);
    f_in = fopen("../input/input.txt", "r");
    for (int i = 0; i < size; i++)
        fscanf(f_in, "%d\n", &in[i]);
    fclose(f_in);
   QueryPerformanceCounter(&time_start);
    InsertionSort(in, size);
QueryPerformanceCounter(&time_over); 
    f_out = fopen("../output/insertion_sort/result_12.txt", "w");
    for (int i = 0; i < size; i++)
    {
        fprintf(f_out, "%d\n", in[i]);
    }
    fclose(f_out);
    tt[3] = endtime - begintime;
    printf("size 2^12,end\n");

    printf("size 2^15,start\n");
    size = pow(2, 15);
    f_in = fopen("../input/input.txt", "r");
    for (int i = 0; i < size; i++)
        fscanf(f_in, "%d\n", &in[i]);
    fclose(f_in);
   QueryPerformanceCounter(&time_start);
    InsertionSort(in, size);
  QueryPerformanceCounter(&time_over); 
    f_out = fopen("../output/insertion_sort/result_15.txt", "w");
    for (int i = 0; i < size; i++)
    {
        fprintf(f_out, "%d\n", in[i]);
    }
    fclose(f_out);
    tt[4] = 1000000 * (time_over.QuadPart - time_start.QuadPart) / dqFreq;
    printf("size 2^15,end\n");

    printf("size 2^18,start\n");
    size = pow(2, 18);
    f_in = fopen("../input/input.txt", "r");
    for (int i = 0; i < size; i++)
        fscanf(f_in, "%d\n", &in[i]);
    fclose(f_in);
  QueryPerformanceCounter(&time_start);
    InsertionSort(in, size);
QueryPerformanceCounter(&time_over); 
    f_out = fopen("../output/insertion_sort/result_18.txt", "w");
    for (int i = 0; i < size; i++)
    {
        fprintf(f_out, "%d\n", in[i]);
    }
    fclose(f_out);
    tt[5] = 1000000 * (time_over.QuadPart - time_start.QuadPart) / dqFreq;

    f_out = fopen("../output/insertion_sort/time.txt", "w");
    for (int i = 0; i < 6; i++)
        fprintf(f_out, "%lf\n", tt[i]);
    fclose(f_out);
    printf("size 2^18,end\n");

    /*
    save = (int *)calloc(size, sizeof(int));
    result = (int *)calloc(size, sizeof(int));
    t = (int *)calloc(k * 5, sizeof(int));
    srand(time(NULL));

    while (k > 0)
    {
    }

    for (int i = 0; i < size; i++)
    {
        array[i] = rand();
        save[i] = array[i];
    }
    //Insertion Sort
    InsertionSort(array, size);
    CopyAndCheck(array, save, size);
    MergeSort(array, 0, size - 1);
    CopyAndCheck(array, save, size);
    HeapSort(array, size);
    CopyAndCheck(array, save, size);
    QuickSort(array, 0, size - 1);
    CopyAndCheck(array, save, size);
    CountingSort(array, result, RAND_MAX, size);
    CopyAndCheck(array, save, size);

    printf("Ending...\n");
    free(array);
    free(save);
    free(result);
    free(t);
    return 0;
}

//copy
int CopyAndCheck(int *a, int *b, int n)
{
    int flag = 1;
    for (int i = 0; i < n - 1; i++)
    {
        if (a[i] > a[i + 1])
            flag = 0;
        a[i] = b[i];
    }
    a[n - 1] = b[n - 1];
    return flag;*/
}
