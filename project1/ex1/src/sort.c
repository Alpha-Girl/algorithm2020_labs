#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include "sort.h"

int CopyAndCheck(int *a, int *b, int n);

int main()
{
    int n, *array, size, *save, *result, k, *t;
    int start, end;
    //print README
    printf("***README***\n");
    printf("————————————————————————————————————————————————————————————————\n");
    printf("The sort.exe will 'k' arraies, of which size are 'n' of 2,\n");
    printf("using InsertionSort,QuickSort,HeapSort,MergeSort,andCountingSort.\n");
    printf("Then it will output the average time of each algorithm.\n");
    printf("————————————————————————————————————————————————————————————————\n");
    //get parameter
    printf("Now plz input k:\n");
    scanf("%d", &k);
    printf("Now plz input n:\n");
    scanf("%d", &n);
    printf("————————————————————————————————————————————————————————————————\n");
    printf("Starting...\n");

    //init
    size = pow(2, n);
    array = (int *)calloc(size, sizeof(int));
    save = (int *)calloc(size, sizeof(int));
    result = (int *)calloc(size, sizeof(int));
    t = (int *)calloc(k * 5, sizeof(int));
    srand(time(NULL));

    while (k>0)
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
    return flag;
}