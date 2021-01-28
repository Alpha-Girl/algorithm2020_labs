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
    return 2 * i;
}

int right(int i)
{
    return 2 * i + 1;
}

int parent(int i)
{
    return i / 2;
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
    for (int i = n; i > 1; i--)
    {
        exchange(&a[1], &a[i]);
        size--;
        MaxHeapify(a, 1, size);
    }
}