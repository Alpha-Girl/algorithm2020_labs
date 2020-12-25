#include "RBT.h"
#include "malloc.h"
#include <windows.h>
#include <time.h>
int in[100];
FILE *f_in, *out1, *time1, *time2, *out2;
void Case_n(int n);
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
    out1 = fopen("../output/inorder.txt", "w");
    time1 = fopen("../output/time1.txt", "w");
    time2 = fopen("../output/time2.txt", "w");
    out2 = fopen("../output/delete_data.txt", "w");
    //n=20，40，60，80，100
    for (int i = 1; i <= 5; i++)
        Case_n(i * 20);
    fclose(out1);
    fclose(out2);
    fclose(time1);
    fclose(time2);
    system("PAUSE");
}

void Case_n(int n)
{
    int choose = rand();
    choose = choose % 4;
    delete_list *List = NULL;
    int i;
    delete_list *new = NULL;
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
    //建树
    RBT *T = create_rbt();
    QueryPerformanceCounter(&time_start);
    for (i = 0; i < n; i++)
    {
        //生成节点
        rbt_node *x = insert_rbt(T, in[i]);
        //记录待删除节点
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
    //中序遍历
    inorder(out1, T, T->node);
    fprintf(out1, "\n");
    QueryPerformanceCounter(&time_start);
    //删除节点
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
    inorder(out2, T, T->node);
    fprintf(out2, "\n");
}
