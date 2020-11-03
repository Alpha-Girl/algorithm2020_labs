#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#ifdef RAND_MAX
    #undef RAND_MAX
#endif
#define RAND_MAX pow(2,n)
void quicksort(int *a,int n);
void heapsort(int *a,int n);
int main(){
    int n,*array,size,*save;
    printf("Please input n:\n");
    scanf("%d",&n);
    size=pow(2,n);
    array=(int*)calloc(size,sizeof(int));
    srand(time(NULL));
    for(int i = 0;i<size;i++){
        array[i]=rand();
        save[i]=array[i];
    }

    free(array);
}