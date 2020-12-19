#include "RBT.h"
#include "malloc.h"
int in[100];
FILE *f_in, *out1, *time1, *time2, *out2;
int main()
{
    f_in = fopen("../input/input.txt", "w");
    //播种随机数，存入input.txt
    srand(time(NULL));
    for (int i = 0; i < 100; i++)
    {
        in[i] = rand();
        fprintf(f_in, "%d\n", in[i]);
    }
    fclose(f_in);
    printf("Finished 1.\n");
}

rbt_node *make_node(int k)
{
    rbt_node *x;
    x = (rbt_node *)calloc(1, sizeof(rbt_node));
    x->color = BLACK;
    x->key = k;
}

void case_n(int n)
{
}