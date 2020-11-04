#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

void InsertionSort(int *a, int n);
void QuickSort(int *a, int n);
void HeapSort(int *a, int n);
void MergeSort(int *a, int start, int end);
void CountSort(int *a, int n);

int main()
{
    int n, *array, size, *save;
    printf("Please input n:\n");
    scanf("%d", &n);
    size = pow(2, n);
    array = (int *)calloc(size, sizeof(int));
    save = (int *)calloc(size, sizeof(int));
    srand(time(NULL));
    for (int i = 0; i < size; i++)
    {
        array[i] = rand();
        save[i] = array[i];
    }
    printf("Starting...\n");
    //Insertion Sort
    free(array);
    free(save);
    return 0;
}

//Insertion Sort
void InsertionSort(int *a, int n)
{
    for (int j = 1; j < n; j++)
    {
        int key = a[j];
        int i = j - 1;
        while (i >= 0 && a[i] > key)
        {
            a[i + 1] = a[i];
            i = i - 1;
        }
        a[i + 1] = key;
    }
}

//Merge Sort
void Merge(int *a, int start, int q, int end)
{
    int m = q - start + 1;
    int n = end - q;
    int *L, *R, i, j;
    L = (int *)calloc(m + 1, sizeof(int));
    R = (int *)calloc(n + 1, sizeof(int));
    for (i = 0; i < m; i++)
        L[i] = a[start + i - 1];
    for (j = 0; j < n; j++)
        R[j] = a[q + j];
    L[m] = INT_MAX;
    R[n] = INT_MAX;
    i = 0;
    j = 0;
    for (int k = start; k <= end; k++)
    {
        if (L[i] <= R[j])
        {
            a[k] = L[i];
            i++;
        }
        else
        {
            a[k] = R[j];
            j++;
        }
    }
    free(L);
    free(R);
}

void MergeSort(int *a, int start, int end)
{
    if (start < end)
    {
        int q = (start + end) / 2;
        MergeSort(a, start, q);
        MergeSort(a, q + 1, end);
        Merge(a, start, q, end);
    }
}