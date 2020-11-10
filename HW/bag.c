#include <stdio.h>
#include <stdlib.h>

int main()
{
    int *a;
    int n, i;
    int size;
    printf("Plz input the n:\n");
    scanf("%d", &n);
    a=(int *)calloc(n.sizeof(int));
    for (i = 0; i < n; i++)
    {
        printf("Plz input the weight of %dth:\n",i+1);
        scanf("%d",&a[i]);
    }
}