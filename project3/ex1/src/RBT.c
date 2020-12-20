#include "RBT.h"
#include "malloc.h"
#include <windows.h>
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
    out1 = fopen("../output/inorder.txt", "w");
    time1 = fopen("../output/time1.txt", "w");
    time2 = fopen("../output/time2.txt", "w");
    out2 = fopen("../output/delete_data.txt", "w");
    for (int i = 1; i <= 5; i++)
    {
        Case_n(i * 20);
    }
}

rbt_node *make_node(int k)
{
    rbt_node *x;
    x = (rbt_node *)calloc(1, sizeof(rbt_node));
    x->color = BLACK;
    x->key = k;
    x->p = NULL;
    x->left = NULL;
    x->right = NULL;
    return x;
}

void Case_n(int n)
{
    int choose = rand();
    choose = choose % 4;
    delete_list *List = NULL;
    int i;
    delete_list *new;

    double run_time;
    LARGE_INTEGER time_start; //开始时间
    LARGE_INTEGER time_over;  //结束时间
    double dqFreq;            //计时器频率
    LARGE_INTEGER f;          //计时器频率
    QueryPerformanceFrequency(&f);
    dqFreq = (double)f.QuadPart;
    QueryPerformanceCounter(&time_start); //计时开始
    QueryPerformanceCounter(&time_over);  //计时结束
    run_time = 1000000 * (time_over.QuadPart - time_start.QuadPart) / dqFreq;
    //乘以1000000把单位由秒化为微秒，精度为1000 000/（cpu主频）微秒

    RBT *T = (RBT *)calloc(1, sizeof(RBT));
    T->nil = (rbt_node *)calloc(1, sizeof(rbt_node));
    T->root = T->nil;
    QueryPerformanceCounter(&time_start);
    for (i = 0; i < n; i++)
    {
        rbt_node *x = make_node(in[i]);
        rbt_insert(T, x);
        if (i % 4 == choose)
        {
            new = (delete_list *)calloc(1, sizeof(delete_list));
            new->next = List;
            new->node = x;
            List = new;
        }
    }
    QueryPerformanceCounter(&time_over);
    run_time = 1000000 * (time_over.QuadPart - time_start.QuadPart) / dqFreq;
    fprintf(time1, "%lf\n", run_time);
    inorder(out1, T, T->root);
    fprintf(out1, "\n");
    QueryPerformanceCounter(&time_start);
    for (i = 0; i < n / 4; i++)
    {
        fprintf(out2, " %d ", List->node->key);
        rbt_delete(T, List->node);
        free(List->node);
        List = List->next;
    }
    QueryPerformanceCounter(&time_over);
    run_time = 1000000 * (time_over.QuadPart - time_start.QuadPart) / dqFreq;
    fprintf(time2, "%lf\n", run_time);
    fprintf(out2, "\n");
    inorder(out2, T, T->root);
    fprintf(out2, "\n");

    while (T->root != T->nil)
    {
        rbt_node *x = T->root;
        rbt_delete(T, T->root);
        free(x);
    }
    free(T);
    free(List);
    free(new);
}