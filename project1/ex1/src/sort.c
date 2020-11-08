#include <windows.h>
#include "sort.h"
int in[262145];
int save[262145];

int CopyAndCheck(int *a, int *b, int n);
void ReadData(int n);
void ReadDatah(int n);
void WriteData(char *filename, int *a, int n);
void WriteDatah(char *filename, int *a, int n);
void WriteTime(char *filename, double *a, int n);
int main()
{
    FILE *f_in;
    int n, *t;
    double tt[6];
    long size;
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
    printf("----------------------------------------------------------------\n");
    printf("2.InsertionSort Starting\n");
    printf("size 2^3,start\n");
    size = pow(2, 3);
    ReadData(size);
    QueryPerformanceCounter(&time_start);
    InsertionSort(in, size);
    QueryPerformanceCounter(&time_over);
    WriteData("../output/insertion_sort/result_3.txt", in, size);
    tt[0] = 1000000 * (time_over.QuadPart - time_start.QuadPart) / dqFreq;
    printf("size 2^3,end\n");

    printf("size 2^6,start\n");
    size = pow(2, 6);
    ReadData(size);
    QueryPerformanceCounter(&time_start);
    InsertionSort(in, size);
    QueryPerformanceCounter(&time_over);
    WriteData("../output/insertion_sort/result_6.txt", in, size);
    tt[1] = 1000000 * (time_over.QuadPart - time_start.QuadPart) / dqFreq;
    printf("size 2^6,end\n");

    printf("size 2^9,start\n");
    size = pow(2, 9);
    ReadData(size);
    QueryPerformanceCounter(&time_start);
    InsertionSort(in, size);
    QueryPerformanceCounter(&time_over);
    WriteData("../output/insertion_sort/result_9.txt", in, size);
    tt[2] = 1000000 * (time_over.QuadPart - time_start.QuadPart) / dqFreq;
    printf("size 2^9,end\n");

    printf("size 2^12,start\n");
    size = pow(2, 12);
    ReadData(size);
    QueryPerformanceCounter(&time_start);
    InsertionSort(in, size);
    QueryPerformanceCounter(&time_over);
    WriteData("../output/insertion_sort/result_12.txt", in, size);
    tt[3] = 1000000 * (time_over.QuadPart - time_start.QuadPart) / dqFreq;
    printf("size 2^12,end\n");

    printf("size 2^15,start\n");
    size = pow(2, 15);
    ReadData(size);
    QueryPerformanceCounter(&time_start);
    InsertionSort(in, size);
    QueryPerformanceCounter(&time_over);
    WriteData("../output/insertion_sort/result_15.txt", in, size);
    tt[4] = 1000000 * (time_over.QuadPart - time_start.QuadPart) / dqFreq;
    printf("size 2^15,end\n");

    printf("size 2^18,start\n");
    size = pow(2, 18);
    ReadData(size);
    QueryPerformanceCounter(&time_start);
    InsertionSort(in, size);
    QueryPerformanceCounter(&time_over);
    WriteData("../output/insertion_sort/result_18.txt", in, size);
    tt[5] = 1000000 * (time_over.QuadPart - time_start.QuadPart) / dqFreq;
    printf("size 2^18,end\n");

    printf("Writing time.txt.\n");
    WriteTime("../output/insertion_sort/time.txt", tt, 6);

    printf("Finished 2.\n");

    //Merge Sort
    printf("----------------------------------------------------------------\n");
    printf("3.MergeSort Starting\n");
    printf("size 2^3,start\n");
    size = pow(2, 3);
    ReadData(size);
    QueryPerformanceCounter(&time_start);
    MergeSort(in, 0, size - 1);
    QueryPerformanceCounter(&time_over);
    WriteData("../output/merge_sort/result_3.txt", in, size);
    tt[0] = 1000000 * (time_over.QuadPart - time_start.QuadPart) / dqFreq;
    printf("size 2^3,end\n");

    printf("size 2^6,start\n");
    size = pow(2, 6);
    ReadData(size);
    QueryPerformanceCounter(&time_start);
    MergeSort(in, 0, size - 1);
    QueryPerformanceCounter(&time_over);
    WriteData("../output/merge_sort/result_6.txt", in, size);
    tt[1] = 1000000 * (time_over.QuadPart - time_start.QuadPart) / dqFreq;
    printf("size 2^6,end\n");

    printf("size 2^9,start\n");
    size = pow(2, 9);
    ReadData(size);
    QueryPerformanceCounter(&time_start);
    MergeSort(in, 0, size - 1);
    QueryPerformanceCounter(&time_over);
    WriteData("../output/merge_sort/result_9.txt", in, size);
    tt[2] = 1000000 * (time_over.QuadPart - time_start.QuadPart) / dqFreq;
    printf("size 2^9,end\n");

    printf("size 2^12,start\n");
    size = pow(2, 12);
    ReadData(size);
    QueryPerformanceCounter(&time_start);
    MergeSort(in, 0, size - 1);
    QueryPerformanceCounter(&time_over);
    WriteData("../output/merge_sort/result_12.txt", in, size);
    tt[3] = 1000000 * (time_over.QuadPart - time_start.QuadPart) / dqFreq;
    printf("size 2^12,end\n");

    printf("size 2^15,start\n");
    size = pow(2, 15);
    ReadData(size);
    QueryPerformanceCounter(&time_start);
    MergeSort(in, 0, size - 1);
    QueryPerformanceCounter(&time_over);
    WriteData("../output/merge_sort/result_15.txt", in, size);
    tt[4] = 1000000 * (time_over.QuadPart - time_start.QuadPart) / dqFreq;
    printf("size 2^15,end\n");

    printf("size 2^18,start\n");
    size = pow(2, 18);
    ReadData(size);
    QueryPerformanceCounter(&time_start);
    MergeSort(in, 0, size - 1);
    QueryPerformanceCounter(&time_over);
    WriteData("../output/merge_sort/result_18.txt", in, size);
    tt[5] = 1000000 * (time_over.QuadPart - time_start.QuadPart) / dqFreq;
    printf("size 2^18,end\n");

    printf("Writing time.txt.\n");
    WriteTime("../output/merge_sort/time.txt", tt, 6);

    printf("Finished 3.\n");

    //Heap Sort
    printf("----------------------------------------------------------------\n");
    printf("4.HeapSort Starting\n");
    printf("size 2^3,start\n");
    size = pow(2, 3);
    ReadDatah(size);
    QueryPerformanceCounter(&time_start);
    HeapSort(in, size);
    QueryPerformanceCounter(&time_over);
    WriteDatah("../output/heap_sort/result_3.txt", in, size);
    tt[0] = 1000000 * (time_over.QuadPart - time_start.QuadPart) / dqFreq;
    printf("size 2^3,end\n");

    printf("size 2^6,start\n");
    size = pow(2, 6);
    ReadDatah(size);
    QueryPerformanceCounter(&time_start);
    HeapSort(in, size);
    QueryPerformanceCounter(&time_over);
    WriteDatah("../output/heap_sort/result_6.txt", in, size);
    tt[1] = 1000000 * (time_over.QuadPart - time_start.QuadPart) / dqFreq;
    printf("size 2^6,end\n");

    printf("size 2^9,start\n");
    size = pow(2, 9);
    ReadDatah(size);
    QueryPerformanceCounter(&time_start);
    HeapSort(in, size);
    QueryPerformanceCounter(&time_over);
    WriteDatah("../output/heap_sort/result_9.txt", in, size);
    tt[2] = 1000000 * (time_over.QuadPart - time_start.QuadPart) / dqFreq;
    printf("size 2^9,end\n");

    printf("size 2^12,start\n");
    size = pow(2, 12);
    ReadDatah(size);
    QueryPerformanceCounter(&time_start);
    HeapSort(in, size);
    QueryPerformanceCounter(&time_over);
    WriteDatah("../output/heap_sort/result_12.txt", in, size);
    tt[3] = 1000000 * (time_over.QuadPart - time_start.QuadPart) / dqFreq;
    printf("size 2^12,end\n");

    printf("size 2^15,start\n");
    size = pow(2, 15);
    ReadDatah(size);
    QueryPerformanceCounter(&time_start);
    HeapSort(in, size);
    QueryPerformanceCounter(&time_over);
    WriteDatah("../output/heap_sort/result_15.txt", in, size);
    tt[4] = 1000000 * (time_over.QuadPart - time_start.QuadPart) / dqFreq;
    printf("size 2^15,end\n");

    printf("size 2^18,start\n");
    size = pow(2, 18);
    ReadDatah(size);
    QueryPerformanceCounter(&time_start);
    HeapSort(in, size);
    QueryPerformanceCounter(&time_over);
    WriteDatah("../output/heap_sort/result_18.txt", in, size);
    tt[5] = 1000000 * (time_over.QuadPart - time_start.QuadPart) / dqFreq;
    printf("size 2^18,end\n");

    printf("Writing time.txt.\n");
    WriteTime("../output/heap_sort/time.txt", tt, 6);

    printf("Finished 4.\n");

    //Quick Sort
    printf("----------------------------------------------------------------\n");
    printf("5.QuickSort Starting\n");
    printf("size 2^3,start\n");
    size = pow(2, 3);
    ReadData(size);
    QueryPerformanceCounter(&time_start);
    QuickSort(in, 0, size - 1);
    QueryPerformanceCounter(&time_over);
    WriteData("../output/quick_sort/result_3.txt", in, size);
    tt[0] = 1000000 * (time_over.QuadPart - time_start.QuadPart) / dqFreq;
    printf("size 2^3,end\n");

    printf("size 2^6,start\n");
    size = pow(2, 6);
    ReadData(size);
    QueryPerformanceCounter(&time_start);
    QuickSort(in, 0, size - 1);
    QueryPerformanceCounter(&time_over);
    WriteData("../output/quick_sort/result_6.txt", in, size);
    tt[1] = 1000000 * (time_over.QuadPart - time_start.QuadPart) / dqFreq;
    printf("size 2^6,end\n");

    printf("size 2^9,start\n");
    size = pow(2, 9);
    ReadData(size);
    QueryPerformanceCounter(&time_start);
    QuickSort(in, 0, size - 1);
    QueryPerformanceCounter(&time_over);
    WriteData("../output/quick_sort/result_9.txt", in, size);
    tt[2] = 1000000 * (time_over.QuadPart - time_start.QuadPart) / dqFreq;
    printf("size 2^9,end\n");

    printf("size 2^12,start\n");
    size = pow(2, 12);
    ReadData(size);
    QueryPerformanceCounter(&time_start);
    QuickSort(in, 0, size - 1);
    QueryPerformanceCounter(&time_over);
    WriteData("../output/quick_sort/result_12.txt", in, size);
    tt[3] = 1000000 * (time_over.QuadPart - time_start.QuadPart) / dqFreq;
    printf("size 2^12,end\n");

    printf("size 2^15,start\n");
    size = pow(2, 15);
    ReadData(size);
    QueryPerformanceCounter(&time_start);
    QuickSort(in, 0, size - 1);
    QueryPerformanceCounter(&time_over);
    WriteData("../output/quick_sort/result_15.txt", in, size);
    tt[4] = 1000000 * (time_over.QuadPart - time_start.QuadPart) / dqFreq;
    printf("size 2^15,end\n");

    printf("size 2^18,start\n");
    size = pow(2, 18);
    ReadData(size);
    QueryPerformanceCounter(&time_start);
    QuickSort(in, 0, size - 1);
    QueryPerformanceCounter(&time_over);
    WriteData("../output/quick_sort/result_18.txt", in, size);
    tt[5] = 1000000 * (time_over.QuadPart - time_start.QuadPart) / dqFreq;
    printf("size 2^18,end\n");

    printf("Writing time.txt.\n");
    WriteTime("../output/quick_sort/time.txt", tt, 6);

    printf("Finished 5.\n");

    //Counting Sort
    printf("----------------------------------------------------------------\n");
    printf("6.CountingSort Starting\n");
    printf("size 2^3,start\n");
    size = pow(2, 3);
    ReadData(size);
    QueryPerformanceCounter(&time_start);
    CountingSort(in, save, 32768, (int)size);
    QueryPerformanceCounter(&time_over);
    WriteData("../output/counting_sort/result_3.txt", save, size);
    tt[0] = 1000000 * (time_over.QuadPart - time_start.QuadPart) / dqFreq;
    printf("size 2^3,end\n");

    printf("size 2^6,start\n");
    size = pow(2, 6);
    ReadData(size);
    QueryPerformanceCounter(&time_start);
    CountingSort(in, save, RAND_MAX, size);
    QueryPerformanceCounter(&time_over);
    WriteData("../output/counting_sort/result_6.txt", save, size);
    tt[1] = 1000000 * (time_over.QuadPart - time_start.QuadPart) / dqFreq;
    printf("size 2^6,end\n");

    printf("size 2^9,start\n");
    size = pow(2, 9);
    ReadData(size);
    QueryPerformanceCounter(&time_start);
    CountingSort(in, save, RAND_MAX, size);
    QueryPerformanceCounter(&time_over);
    WriteData("../output/counting_sort/result_9.txt", save, size);
    tt[2] = 1000000 * (time_over.QuadPart - time_start.QuadPart) / dqFreq;
    printf("size 2^9,end\n");

    printf("size 2^12,start\n");
    size = pow(2, 12);
    ReadData(size);
    QueryPerformanceCounter(&time_start);
    CountingSort(in, save, RAND_MAX, size);
    QueryPerformanceCounter(&time_over);
    WriteData("../output/counting_sort/result_12.txt", save, size);
    tt[3] = 1000000 * (time_over.QuadPart - time_start.QuadPart) / dqFreq;
    printf("size 2^12,end\n");

    printf("size 2^15,start\n");
    size = pow(2, 15);
    ReadData(size);
    QueryPerformanceCounter(&time_start);
    CountingSort(in, save, RAND_MAX, size);
    QueryPerformanceCounter(&time_over);
    WriteData("../output/counting_sort/result_15.txt", save, size);
    tt[4] = 1000000 * (time_over.QuadPart - time_start.QuadPart) / dqFreq;
    printf("size 2^15,end\n");

    printf("size 2^18,start\n");
    size = pow(2, 18);
    ReadData(size);
    QueryPerformanceCounter(&time_start);
    CountingSort(in, save, RAND_MAX, size);
    QueryPerformanceCounter(&time_over);
    WriteData("../output/counting_sort/result_18.txt", save, size);
    tt[5] = 1000000 * (time_over.QuadPart - time_start.QuadPart) / dqFreq;
    printf("size 2^18,end\n");

    printf("Writing time.txt.\n");
    WriteTime("../output/counting_sort/time.txt", tt, 6);

    printf("Finished 6.\n");
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

void ReadData(int n)
{
    FILE *f_in;
    f_in = fopen("../input/input.txt", "r");
    for (int i = 0; i < n; i++)
        fscanf(f_in, "%d\n", &in[i]);
    fclose(f_in);
}
void ReadDatah(int n)
{
    FILE *f_in;
    f_in = fopen("../input/input.txt", "r");
    for (int i = 1; i <= n; i++)
        fscanf(f_in, "%d\n", &in[i]);
    fclose(f_in);
}
void WriteData(char *filename, int *a, int n)
{
    FILE *f_out;
    f_out = fopen(filename, "w");
    for (int i = 0; i < n; i++)
    {
        fprintf(f_out, "%d\n", a[i]);
    }
    fclose(f_out);
}
void WriteDatah(char *filename, int *a, int n)
{
    FILE *f_out;
    f_out = fopen(filename, "w");
    for (int i = 1; i <= n; i++)
    {
        fprintf(f_out, "%d\n", a[i]);
    }
    fclose(f_out);
}
void WriteTime(char *filename, double *a, int n)
{
    FILE *f_out;
    f_out = fopen(filename, "w");
    for (int i = 0; i < n; i++)
    {
        fprintf(f_out, "%lf\n", a[i]);
    }
    fclose(f_out);
}