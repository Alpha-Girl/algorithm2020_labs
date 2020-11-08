#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <limits.h>
void InsertionSort(int *a, int n);
void QuickSort(int *a, int start, int end);
void HeapSort(int *a, int n);
void MergeSort(int *a, int start, int end);
void CountingSort(int *a, int *b, int length, int n);

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
        L[i] = a[start + i];
    for (j = 1; j <= n; j++)
        R[j - 1] = a[q + j];
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

//Heap Sort
void exchange(int *a, int *b)
{
    int t;
    t = *a;
    *a = *b;
    *b = t;
}

int Left(int i)
{
    return 2 *i;
}

int right(int i)
{
    return 2 * i+1;
}

int parent(int i)
{
    return i/2;
}

void MaxHeapify(int *a, int target, int n)
{
    int l, r, largest;
    l = Left(target);
    r = right(target);
    if (l <= n && a[l] > a[target])
        largest = l;
    else
        largest = target;
    if (r <= n && a[r] > a[largest])
        largest = r;
    if (largest != target)
    {
        exchange(&a[largest], &a[target]);
        MaxHeapify(a, largest, n);
    }
}

void BuildMaxHeap(int *a, int n)
{
    for (int i = n / 2; i >= 1; i--)
        MaxHeapify(a, i, n);
}

void HeapSort(int *a, int n)
{
    int size = n;
    BuildMaxHeap(a, n);
    for (int i = n ; i > 1; i--)
    {
        exchange(&a[1], &a[i]);
        size--;
        MaxHeapify(a,1, size);
    }
}

//Quick Sort
int Partition(int *a, int start, int end)
{
    int x = a[end];
    int i = start - 1;
    for (int j = start; j < end; j++)
    {
        if (a[j] <= x)
        {
            i++;
            exchange(&a[i], &a[j]);
        }
    }
    exchange(&a[i + 1], &a[end]);
    return i + 1;
}

void QuickSort(int *a, int start, int end)
{
    if (start < end)
    {
        int q = Partition(a, start, end);
        QuickSort(a, start, q - 1);
        QuickSort(a, q + 1, end);
    }
}

//Counting Sort
void CountingSort(int *a, int *b, int length, int n)
{
    int *c, i, j;
    c = (int *)calloc(length, sizeof(int));
    for (i = 0; i < length; i++)
        c[i] = 0;
    for (j = 0; j < n; j++)
        c[a[j]] = c[a[j]] + 1;
    for (i = 1; i < length; i++)
        c[i] = c[i] + c[i - 1];
    for (j = n - 1; j >= 0; j++)
    {
        b[c[a[j]] - 1] = a[j];
        c[a[j]] = c[a[j]] - 1;
    }
    free(c);
}
